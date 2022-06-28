
#define ZLIB

#ifdef ZLIB
#include <zlib.h>
#elif defined(ISAL)
#include "include/igzip_lib.h"
#elif defined(LIBDEFLATE)
#include "libdeflate.h"
#endif

#include "return_codes.h"

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#define uchar unsigned char

bool check_IDAT(size_t pos, const uchar *mas)
{
    return mas[pos] == 'I' && mas[pos + 1] == 'D' && mas[pos + 2] == 'A' && mas[pos + 3] == 'T';
}
bool check_IEND(size_t pos, const uchar *mas)
{
    return mas[pos] == 'I' && mas[pos + 1] == 'E' && mas[pos + 2] == 'N' && mas[pos + 3] == 'D';
}
bool check_PLTE(size_t pos, const uchar *mas)
{
    return mas[pos] == 'P' && mas[pos + 1] == 'L' && mas[pos + 2] == 'T' && mas[pos + 3] == 'E';
}
void processing_error(int code)
{
    if (code == 1)
        perror("Incorrect count of program arguments");
    if (code == 2)
        perror("The input file could not be opened for reading");
    if (code == 3)
        perror("failed to allocate memory");
    if (code == 4)
        perror("Could not open the output file for writing");
    if (code == 5)
        perror("Incorrect first argument");
    if (code == 6)
        perror("Incorrect PNG file");
}
int get_number(const int start, const int end, const uchar *mas)
{
    int res = 0;
    int offset = 1;
    for (int i = end - 1; i >= start; --i)
    {
        uchar x = mas[i];
        int pos = offset;
        while (x > 0)
        {
            res += (x % 2) * pos;
            x /= 2;
            pos *= 2;
        }
        offset *= 256;
    }
    return res;
}

uchar paeth_predictor(uchar a, uchar b, uchar c)
{
    int p = a + b - c;
    int pa = abs(p - a);
    int pb = abs(p - b);
    int pc = abs(p - c);
    if (pa <= pb && pa <= pc)
    {
        return a;
    }
    if (pb <= pc)
    {
        return b;
    }
    return c;
}

uchar recon_0(uchar x, uchar a, uchar b, uchar c)
{
    return x;
}
uchar recon_1(uchar x, uchar a, uchar b, uchar c)
{
    return x + a;
}
uchar recon_2(uchar x, uchar a, uchar b, uchar c)
{
    return x + b;
}
uchar recon_3(uchar x, uchar a, uchar b, uchar c)
{
    return x + (a + b) / 2;
}
uchar recon_4(uchar x, uchar a, uchar b, uchar c)
{
    return x + paeth_predictor(a, b, c);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        processing_error(1);
        return ERROR_INVALID_DATA;
    }

    FILE *read = fopen(argv[1], "rb");
    if (read == NULL)
    {
        processing_error(2);
        return ERROR_FILE_NOT_FOUND;
    }

    int position = ftell(read);
    fseek(read, 0, SEEK_END);
    size_t count_pixels = ftell(read) - position;
    fseek(read, position, 0);

    if (count_pixels < 37)
    {
        processing_error(6);
        fclose(read);
        return ERROR_INVALID_DATA;
    }

    uchar *mas = malloc(sizeof(uchar) * count_pixels);
    if (mas == NULL)
    {
        processing_error(3);
        fclose(read);
        return ERROR_OUTOFMEMORY;
    }

    fread(mas, count_pixels, sizeof(uchar), read);
    fclose(read);

    int weight = get_number(16, 20, mas);
    int height = get_number(20, 24, mas);
    int bit_depth = get_number(24, 25, mas);
    int color_type = get_number(25, 26, mas);
    int compression = get_number(26, 27, mas);
    int filter = get_number(27, 28, mas);
    int interlace = get_number(28, 29, mas);
    if (mas[0] != 0x89 || mas[1] != 'P' || mas[2] != 'N' || mas[3] != 'G' || mas[4] != 0x0D || mas[5] != 0x0A ||
        mas[6] != 0x1A || mas[7] != 0x0A || mas[12] != 'I' || mas[13] != 'H' || mas[14] != 'D' || mas[15] != 'R' ||
        compression != 0 || color_type != 0 && color_type != 2 || filter != 0 || interlace != 0 || bit_depth != 8)
    {
        processing_error(6);
        free(mas);
        return ERROR_INVALID_DATA;
    }

    int byte_depth = 1;
    if (color_type == 2)
    {
        byte_depth = 3;
    }
    int pos = 33;
    int ok = 0;
    do
    {
        if (pos + 4 >= count_pixels)
            break;
        int local_size = get_number(pos, pos + 4, mas);
        pos += 4;
        if (pos + 4 >= count_pixels)
            break;
        if (color_type == 0 && check_PLTE(pos, mas))
        {
            free(mas);
            processing_error(6);
            return ERROR_INVALID_DATA;
        }
        if (check_IDAT(pos, mas))
        {
            pos -= 4;
            ++ok;
            break;
        }
        pos += local_size + 8;
    } while (pos < count_pixels);

    if (ok == 0)
    {
        free(mas);
        processing_error(6);
        return ERROR_INVALID_DATA;
    }

    uchar *compress_idat = malloc(0);
    int global_size = 0;
    do
    {
        if (pos + 4 >= count_pixels)
            break;
        int local_size = get_number(pos, pos + 4, mas);
        pos += 4;
        if (pos + 4 >= count_pixels)
            break;
        if (!check_IDAT(pos, mas))
        {
            pos -= 4;
            break;
        }
        pos += 4;
        if (pos + local_size + 4 >= count_pixels)
            break;
        uchar *copy = realloc(compress_idat, (global_size + local_size) * sizeof(uchar));
        if (copy != NULL)
        {
            compress_idat = copy;
            for (size_t i = 0; i < local_size; ++i)
            {
                compress_idat[i + global_size] = mas[pos + i];
            }
            pos += local_size + 4;
            global_size += local_size;
        }
        else
        {
            free(compress_idat);
            free(mas);
            processing_error(3);
            return ERROR_OUTOFMEMORY;
        }
    } while (pos < count_pixels);

    do
    {
        if (pos + 4 >= count_pixels)
            break;
        int local_size = get_number(pos, pos + 4, mas);
        pos += 4;
        if (pos + 4 >= count_pixels)
            break;
        if (check_IDAT(pos, mas))
        {
            free(mas);
            free(compress_idat);
            processing_error(6);
            return ERROR_INVALID_DATA;
        }
        if (check_IEND(pos, mas))
        {
            ++ok;
            break;
        }
        pos += local_size + 8;
    } while (pos < count_pixels);

    free(mas);
    if (ok == 1)
    {
        free(compress_idat);
        processing_error(6);
        return ERROR_INVALID_DATA;
    }

    int w = weight * byte_depth + 1;

    int size = height * w;
    uchar *idat = malloc(sizeof(uchar) * size);
    if (idat == NULL)
    {
        processing_error(3);
        free(compress_idat);
        return ERROR_OUTOFMEMORY;
    }
    int check;
#if defined(ZLIB)
    check = uncompress(idat, (uLongf *)&size, compress_idat, global_size);
    free(compress_idat);
    if (check != 0)
    {
        free(idat);
        processing_error(6);
        return ERROR_INVALID_DATA;
    }
#elif defined(ISAL)
    struct inflate_state my;
    my.avail_in = global_size;
    my.avail_out = size;
    my.next_in = compress_idat;
    my.next_out = idat;
    my.crc_flag = ISAL_ZLIB;
    check = isal_inflate_stateless(&my);
    free(compress_idat);
    if (check != ISAL_DECOMP_OK)
    {
        free(idat);
        processing_error(6);
        return ERROR_INVALID_DATA;
    }
#elif defined(LIBDEFLATE)
    check = libdeflate_zlib_decompress(libdeflate_alloc_decompressor(), compress_idat, global_size, idat, size, &size);
    free(compress_idat);
    if (check != LIBDEFLATE_SUCCESS)
    {
        free(idat);
        processing_error(6);
        return ERROR_INVALID_DATA;
    }
#endif
    uchar *result = malloc(sizeof(uchar) * weight * height * byte_depth);
    if (result == NULL)
    {
        processing_error(3);
        free(idat);
        return ERROR_OUTOFMEMORY;
    }
    pos = 0;
    for (int i = 0; i < height; i++)
    {
        int filter_type = get_number(i * w, i * w + 1, idat);
        uchar (*operation)(uchar x, uchar a, uchar b, uchar c);
        if (filter_type == 0)
        {
            operation = recon_0;
        }
        if (filter_type == 1)
        {
            operation = recon_1;
        }
        if (filter_type == 2)
        {
            operation = recon_2;
        }
        if (filter_type == 3)
        {
            operation = recon_3;
        }
        if (filter_type == 4)
        {
            operation = recon_4;
        }
        uchar a = 0, b = 0, c = 0;
        for (int j = 1; j < w; j++)
        {
            int ind = i * w + j;
            if (j > byte_depth)
            {
                a = idat[ind - byte_depth];
            }
            if (i > 0)
            {
                b = idat[ind - w];
            }
            if (j > byte_depth && i > 0)
            {
                c = idat[ind - w - byte_depth];
            }
            result[pos] = operation(idat[ind], a, b, c);
            idat[ind] = result[pos];
            pos++;
        }
    }
    free(idat);

    int type = 5;
    if (byte_depth == 3)
    {
        type = 6;
    }
    FILE *write = fopen(argv[2], "wb");
    if (write == NULL)
    {
        processing_error(4);
        free(result);
        return ERROR_FILE_NOT_FOUND;
    }
    fprintf(write, "P%i\n%i %i\n%i\n", type, weight, height, 255);
    fwrite(result, sizeof(uchar), weight * height * byte_depth, write);
    free(result);
    fclose(write);
    return ERROR_SUCCESS;
}
