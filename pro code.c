#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct image
{
    char magic[10];
    char comment[50];
    int width;
    int height;
    int depth;
    unsigned char** img;
} IMAGE;

int ImageBrightness(IMAGE* in, IMAGE* out, int val);
int ImageFlip(IMAGE* in, IMAGE* out, int mode);
int ImageSizeChange(IMAGE* in, IMAGE* out, float ratio);
int findEdge(IMAGE* in, IMAGE* out);

int menu(void);

int main (void)
{
    FILE *fpr, *fpw;

    IMAGE src, dest;
    int i, j, ctl, mod, menu_id;
    float ratio;

    char fname[100], fname_new[100];
    char fpath[100] = "\"C:\\Program Files\\IrfanView\\i_view64.exe\"";
    char fpath_new[100] = "\"C:\\Program Files\\IrfanView\\i_view64.exe\"";

    printf("Enter the input file name: ");
    scanf("%s", fname);

    printf("Enter the output file name: ");
    scanf("%s", fname_new);

    strcat(fpath, " ");
    strcat(fpath, fname);
    system(fpath);

    fpr = fopen(fname, "r");
    if (fpr == NULL)
    {
        printf("cannot open input file\n");
        exit(1);
    }

    //read header from src file
    fgets(src.magic, 10, fpr);
    fgets(src.comment, 50, fpr);
    fscanf(fpr, "%d", &src.width);
    fscanf(fpr, "%d", &src.height);
    fscanf(fpr, "%d", &src.depth);

    //2d memory allocation for src file
    src.img = (unsigned char**)malloc(src.height*sizeof(unsigned char*));
    for (i = 0; i < src.height; i++)
        src.img[i] = (unsigned char*)malloc(src.width*sizeof(unsigned char));
    if (src.img == NULL)
    {
        printf("fail to allocate the memory\n");
        exit(1);
    }

    //info for dest file
    strcpy(dest.magic, src.magic);
    strcpy(dest.comment, src.comment);
    dest.width = src.width;
    dest.height = src.height;
    dest.depth = src.depth;
/*
    //2d memory allocation for dest file
    dest.img = (unsigned char**)malloc(dest.height*sizeof(unsigned char*));
    for (i = 0; i < dest.height; i++)
        dest.img[i] = (unsigned char*)malloc(dest.width*sizeof(unsigned char));
    if (dest.img == NULL)
    {
        printf("fail to allocate the memory\n");
        exit(1);
    }

    for (i = 0; i < src.height; i++)
        for (j = 0; j < src.width; j++)
            fscanf(fpr, "%hhd", &src.img[i][j]);
*/
    menu_id = menu();
    switch (menu_id)
    {
    case 1:
        printf("Enter the control value for image brightness:");
        scanf("%d", &ctl);

        //2d memory allocation for dest file
        dest.img = (unsigned char**)malloc(dest.height * sizeof(unsigned char*));
        for (i = 0; i < dest.height; i++)
            dest.img[i] = (unsigned char*)malloc(dest.width * sizeof(unsigned char));
        if (dest.img == NULL)
        {
            printf("fail to allocate the memory\n");
            exit(1);
        }

        for (i = 0; i < src.height; i++)
            for (j = 0; j < src.width; j++)
                fscanf(fpr, "%d", &src.img[i][j]);

        ImageBrightness(&src, &dest, ctl);
        break;
    case 2:
        printf("Enter the mode for image flip:");
        scanf("%d", &mod);
        
        //2d memory allocation for dest file
        dest.img = (unsigned char**)malloc(dest.height * sizeof(unsigned char*));
        for (i = 0; i < dest.height; i++)
            dest.img[i] = (unsigned char*)malloc(dest.width * sizeof(unsigned char));
        if (dest.img == NULL)
        {
            printf("fail to allocate the memory\n");
            exit(1);
        }

        for (i = 0; i < src.height; i++)
            for (j = 0; j < src.width; j++)
                fscanf(fpr, "%d", &src.img[i][j]);

        ImageFlip(&src, &dest, mod);
        break;
    case 3:
        printf("Enter the ratio for image size change:");
        scanf("%f", &ratio);

        dest.width = (int)(src.width*ratio);
        dest.height = (int)(src.height*ratio);

        //2d memory allocation for dest file
        dest.img = (unsigned char**)malloc(dest.height * sizeof(unsigned char*));
        for (i = 0; i < dest.height; i++)
            dest.img[i] = (unsigned char*)malloc(dest.width * sizeof(unsigned char));
        if (dest.img == NULL)
        {
            printf("fail to allocate the memory\n");
            exit(1);
        }

        for (i = 0; i < src.height; i++)
            for (j = 0; j < src.width; j++)
                fscanf(fpr, "%d", &src.img[i][j]);

        ImageSizeChange(&src, &dest, ratio);
        break;
    case 4:
    
        //2d memory allocation for dest file
        dest.img = (unsigned char**)malloc(dest.height * sizeof(unsigned char*));
        for (i = 0; i < dest.height; i++)
            dest.img[i] = (unsigned char*)malloc(dest.width * sizeof(unsigned char));
        if (dest.img == NULL)
        {
            printf("fail to allocate the memory\n");
            exit(1);
        }

        for (i = 0; i < src.height; i++)
            for (j = 0; j < src.width; j++)
                fscanf(fpr, "%d", &src.img[i][j]);

        findEdge(&src, &dest);
        break;
    case 5:
        exit(1);
        break;
    default:
        printf("incorrect menu!\n");
        break;
    }

    fpw = fopen(fname_new, "w");
    if (fpw == NULL)
    {
        printf("cannot open new file");
        exit(1);
    }

 // write header
    fputs(dest.magic, fpw);
    fputs(dest.comment, fpw);
    fprintf(fpw, "%d %d\n", dest.width, dest.height);
    fprintf(fpw, "%d\n", dest.depth);
    
    for (i = 0; i < dest.height; i++)
        for (j = 0; j < dest.width; j++)
            fprintf(fpw, "%d\n", dest.img[i][j]);
    
    fclose(fpw);
    fclose(fpr);

    strcat(fpath_new, " ");
    strcat(fpath_new, fname_new);

    system(fpath_new);

    for (i = 0; i < dest.height; i++)
        free(dest.img[i]);
    free(dest.img);

    for (i = 0; i < src.height; i++)
        free(src.img[i]);
    free(src.img);

 
    return 0;
}

int ImageBrightness(IMAGE* in, IMAGE* out, int val)
{
    int i, j, pixel;
 
    //pixel = pixel + val
    for (i = 0; i < in->height; i++)
        for (j = 0; j < in->width; j++)
        {
            pixel = in->img[i][j] + val;
            if (pixel > 255)
                out->img[i][j] = 255;
            else if(pixel < 0)
                out->img[i][j] = 0;
            else
                out->img[i][j] = pixel;
        }

    return 0;
}

int ImageFlip(IMAGE* in, IMAGE* out, int mode)
{
    int i, j;

    //image flip
    if (mode == 1)  //left-right flip
    {
        for (i = 0; i < out->height; i++)
            for (j = 0; j < out->width; j++)
                 out->img[i][j] = in->img[i][in->width-1-j];
     }
    else if(mode == 2)  //up-bottom flip
    {
        for (i = 0; i < out->height; i++)
            for (j = 0; j < out->width; j++)
                 out->img[i][j] = in->img[in->height-1-i][j];
     }

    return 0;
}

int ImageSizeChange(IMAGE* in, IMAGE* out, float ratio)
{
    int i, j;

    if (ratio == 2.)
    {
        for (i = 0; i < out->height; i++)
            for (j = 0; j < out->width; j++)
                out->img[i][j] = in->img[i>>1][j>>1];
     }
    else if (ratio == .5)
    {
        for (i = 0; i < out->height; i++)
            for (j = 0; j < out->width; j++)
                out->img[i][j] = in->img[i<<1][j<<1];
    }

    return 0;
}

int findEdge(IMAGE* in, IMAGE* out)
{
    int i, j;
    double val;
    short **garo, **sero;

    //2d memory allocation for dest file
    garo = (short**)malloc(in->height * sizeof(short*));
    for (i = 0; i < in->height; i++)
            garo[i] = (short*)malloc(in->width * sizeof(short));
        if (garo == NULL)
        {
            printf("fail to allocate the memory\n");
            exit(1);
        }

    //2d memory allocation for dest file
    sero = (short**)malloc(in->height * sizeof(short*));
    for (i = 0; i < in->height; i++)
            sero[i] = (short*)malloc(in->width * sizeof(short));
        if (sero == NULL)
        {
            printf("fail to allocate the memory\n");
            exit(1);
        }  

    for (i = 0; i < out->height; i++)
    {
        for (j = 0; j < (out->width - 1); j++)
            garo[i][j] = in->img[i][j + 1] - in->img[i][j];
        garo[i][out->width - 1] = 0;
    }    

    for (j = 0; i < out->width; j++)
    {
        for (i = 0; i < (out->height - 1); i++)
            sero[i][j] = in->img[i + 1][j] - in->img[i][j];
        sero[out->height - 1][j] = 0;
    }    

    for (i = 0; i <out->height; i++)
        for (j = 0; j < out->width; j++)
        {
            val = sqrt(garo[i][j]*garo[i][j] + sero[i][j]*sero[i][j]);
            if (val > 255.0)
                out->img[i][j] = 255;
            else
                out->img[i][j] = (unsigned char)val;
        }
        
    for (i = 0; i < in->height; i++)
        free(sero[i]);
    free(sero);
    
    for (i = 0; i < in->height; i++)
        free(garo[i]);
    free(garo);

    return 0;
}

int menu(void)
{
    int id;

    system("cls");

    do
    {
        printf("\t\t\t select an item. \n\n ");
        printf("\t\t\t 1. change brightness (positive for brighter, negative for darker image) \n ");
        printf("\t\t\t 2. flip image (1 for left-right flip, 2 for up-bottom flip) \n ");
        printf("\t\t\t 3. change image size (2 for larger, 0.5 for smaller image) \n ");
        printf("\t\t\t 4. find image edges \n ");
        printf("\t\t\t 5. quit the program \n ");
        
        scanf("%d", &id);
    } while (id < 1 || id > 5);

    return id;
}