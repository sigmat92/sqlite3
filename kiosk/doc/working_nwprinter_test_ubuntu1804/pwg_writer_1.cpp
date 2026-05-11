#include <cups/raster.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("usage: %s input.pgm output.pwg\n", argv[0]);
        return 1;
    }

    FILE *pgm = fopen(argv[1], "rb");

    if (!pgm)
    {
        perror("pgm");
        return 1;
    }

    FILE *out = fopen(argv[2], "wb");

    if (!out)
    {
        perror("out");
        fclose(pgm);
        return 1;
    }

    char magic[3];

    int width;
    int height;
    int maxval;

    fscanf(pgm, "%2s", magic);

    if (strcmp(magic, "P5") != 0)
    {
        printf("Only binary PGM (P5) supported\n");

        fclose(pgm);
        fclose(out);

        return 1;
    }

    fscanf(pgm, "%d %d", &width, &height);
    fscanf(pgm, "%d", &maxval);

    // Skip whitespace after header
    fgetc(pgm);

    printf("Input image: %dx%d\n", width, height);

    cups_raster_t *raster =
        cupsRasterOpen(fileno(out), CUPS_RASTER_WRITE_PWG);

    if (!raster)
    {
        printf("Failed to open PWG raster stream\n");

        fclose(pgm);
        fclose(out);

        return 1;
    }

    cups_page_header2_t h;

    memset(&h, 0, sizeof(h));

    // -------------------------------------------------
    // Required PWG/AirPrint fields
    // -------------------------------------------------

    strcpy(h.MediaClass, "PwgRaster");
    strcpy(h.MediaColor, "White");
    strcpy(h.MediaType, "stationery");
    strcpy(h.OutputType, "Gray");

    // 300 DPI
    h.HWResolution[0] = 300;
    h.HWResolution[1] = 300;

    // A4 size in POINTS (1/72 inch)
    h.PageSize[0] = 595;
    h.PageSize[1] = 842;

    // Raster dimensions in PIXELS
    h.cupsWidth  = width;
    h.cupsHeight = height;

    // Bounding box
    h.ImagingBoundingBox[0] = 0;
    h.ImagingBoundingBox[1] = 0;
    h.ImagingBoundingBox[2] = width;
    h.ImagingBoundingBox[3] = height;

    // Grayscale 8-bit
    h.cupsBitsPerColor = 8;
    h.cupsBitsPerPixel = 8;

    h.cupsBytesPerLine = width;

    // sgray_8
    h.cupsColorSpace = CUPS_CSPACE_SW;

    h.cupsColorOrder = CUPS_ORDER_CHUNKED;

    h.cupsNumColors = 1;

    // No compression
    h.cupsCompression = 0;

    // Optional but helps HP printers
    h.cupsInteger[0] = 1;

    // -------------------------------------------------

    if (!cupsRasterWriteHeader2(raster, &h))
    {
        printf("Failed to write PWG header\n");

        cupsRasterClose(raster);

        fclose(pgm);
        fclose(out);

        return 1;
    }

    unsigned char *row =
        (unsigned char *)malloc(width);

    if (!row)
    {
        printf("Memory allocation failed\n");

        cupsRasterClose(raster);

        fclose(pgm);
        fclose(out);

        return 1;
    }

    for (int y = 0; y < height; y++)
    {
        size_t n = fread(row, 1, width, pgm);

        if (n != (size_t)width)
        {
            printf("Short read at row %d\n", y);
            break;
        }

        if (!cupsRasterWritePixels(raster, row, width))
        {
            printf("Failed writing raster row %d\n", y);
            break;
        }
    }

    free(row);

    cupsRasterClose(raster);

    fclose(pgm);
    fclose(out);

    printf("PWG raster created successfully\n");

    return 0;
}
