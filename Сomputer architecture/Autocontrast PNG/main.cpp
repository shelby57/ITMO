#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <omp.h>

#pragma GCC optimize("O3")

typedef unsigned char uchar;
using namespace std;

struct node
{
    float mn, mx;
};
int num_thread, block;
float kf;

int readFile(int &argc, char *argv[], int &type, int &w, int &h, int &dummy, uchar **pixel)
{
    if (argc != 5)
    {
        cerr << "invalid number of arguments";
        return 2;
    }
    FILE *f_in = fopen(argv[2], "rb");
    if (f_in == NULL)
    {
        cerr << "Invalid input file";
        fclose(f_in);
        return 3;
    }

    fscanf(f_in, "P%i%i%i%i\n", &type, &w, &h, &dummy);

    if ((type < 5 || type > 6) || (w <= 0 || h <= 0) || (dummy != 255))
    {
        cerr << "Incorrect parameters";
        fclose(f_in);
        return 4;
    }

    if (type == 5)
    {
        *pixel = (uchar *) malloc(sizeof(uchar) * h * w);
    }
    else
    {
        *pixel = (uchar *) malloc(sizeof(uchar) * h * w * 3);
    }
    if (*pixel == NULL)
    {
        cerr << "Allocation memory failed";
        fclose(f_in);
        return 5;
    }
    int startPosition = ftell(f_in);
    fseek(f_in, 0, SEEK_END);
    int countPixels = ftell(f_in) - startPosition;
    fseek(f_in, startPosition, 0);
    if (type == 5)
    {
        if (countPixels != w * h)
        {
            cerr << "Not enough data";
            fclose(f_in);
            return 6;
        }
        fread(*pixel, sizeof(uchar), w * h, f_in);
    }
    else
    {
        if (countPixels != w * h * 3)
        {
            cerr << "Not enough data";
            fclose(f_in);
            return 6;
        }
        fread(*pixel, sizeof(uchar), w * h * 3, f_in);
    }
    fclose(f_in);
    return 0;
}

uchar get_pixel(node x, unsigned char p)
{
    if (x.mx == x.mn)
    {
        return p;
    }
    float pix = (p - x.mn) / (x.mx - x.mn);
    if (pix >= 1.0)
    {
        return 255;
    }
    if (pix <= 0.0)
    {
        return 0;
    }
    return pix * 255;
}

node get_minmax(int *cnt, int flag)
{
    int sum = 0;
    int mn = 0, mx = 0;
    for (int i = 0; i < 256; ++i)
    {
        sum += cnt[i];
        if (sum > flag)
        {
            mn = i;
            break;
        }
    }
    sum = 0;
    for (int i = 255; i >= 0; --i)
    {
        sum += cnt[i];
        if (sum > flag)
        {
            mx = i;
            break;
        }
    }
    return {mn + 0.0f, mx + 0.0f};
}

void update_pixels_value(int *cnt, node x)
{
    for (int i = 0; i < 256; ++i)
        cnt[i] = get_pixel(x, i);
}

void go_pgm(uchar *pixel, int &size)
{
    int global_cnt[256] = {0};
    omp_set_num_threads(num_thread);
    int step = block * 3;
#pragma omp parallel for default(none) shared(pixel, size, step, block, global_cnt) schedule(static, block)
    for (int i = 0; i < size; i += step)
    {
        int cnt[256] = {0};
        for (int i1 = i; i1 < min(size, i + step); ++i1)
        {
            ++cnt[(pixel)[i1]];
        }
#pragma omp critical
        {
            for (int j = 0; j < 256; ++j)
            {
                global_cnt[j] += cnt[j];
            }
        }
    }
    node x = get_minmax(global_cnt, size * kf);
    update_pixels_value(global_cnt, x);
#pragma omp parallel for default(none) shared(size, pixel, global_cnt, block) schedule(static, block)
    for (int i = 0; i < size; ++i)
    {
        (pixel)[i] = global_cnt[(pixel)[i]];
    }
}

void go_ppm(uchar *pixel, int size)
{
    int global_r[256] = {0}, global_b[256] = {0}, global_g[256] = {0};
    omp_set_num_threads(num_thread);
    int step = 3 * block;
#pragma omp parallel for default(none) shared(pixel, size, step, block, global_r, global_b, global_g) schedule(static, block)
    for (int i = 0; i < size; i += step)
    {
        int r[256] = {0}, g[256] = {0}, b[256] = {0};
        for (int i1 = i; i1 < min(size, i + step); i1 += 3)
        {
            ++r[(pixel)[i1]];
            ++g[(pixel)[i1 + 1]];
            ++b[(pixel)[i1 + 2]];
        }
#pragma omp critical
        {
            for (int j = 0; j < 256; ++j)
            {
                global_r[j] += r[j];
                global_g[j] += g[j];
                global_b[j] += b[j];
            }
        }
    }
    int flag = (size / 3) * kf;
    node rr = get_minmax(global_r, flag);
    node gg = get_minmax(global_b, flag);
    node bb = get_minmax(global_g, flag);
    node x = {min(min(rr.mn, gg.mn), bb.mn), max(max(rr.mx, gg.mx), bb.mx)};
    update_pixels_value(global_r, x);
#pragma omp parallel for default(none)  shared(size, pixel, global_r, block) schedule(static, block)
    for (int i = 0; i < size; ++i)
    {
        (pixel)[i] = global_r[(pixel)[i]];
    }
}

int main(int argc, char *argv[])
{
    int type, w, h, dummy;
    uchar *pixel;
    int result = readFile(argc, argv, type, w, h, dummy, &pixel);
    if (result == 0)
    {
        char *fileName_out = argv[3];
        num_thread = stoi(argv[1]);
        kf = stof(argv[4]);

        if (kf < 0 || kf >= 0.5)
        {
            cerr << "Invalid kf";
            free(pixel);
            return 7;
        }
        if (fileName_out == NULL)
        {
            cerr << "Invalid output file";
            free(pixel);
            return 8;
        }
        FILE *f_out = fopen(fileName_out, "wb");
        if (f_out == NULL)
        {
            cerr << "Allocation memory failed";
            free(pixel);
            return 9;
        }
        int size = w * h;
        block = (w + h) / 2;
        double start_time = omp_get_wtime();
        if (type == 5)
        {
            go_pgm(&*pixel, size);
        }
        else if (type == 6)
        {
            size *= 3;
            go_ppm(&*pixel, size);
        }
        double end_time = omp_get_wtime();
        cout << (end_time - start_time) * 1000 << "mc" << endl;
        fprintf(f_out, "P%i\n%i %i\n%i\n", type, w, h, dummy);
        fwrite(pixel, sizeof(uchar), size, f_out);
        free(pixel);
        fclose(f_out);
        return 0;
    }
    else
    {
        return result;
    }
}