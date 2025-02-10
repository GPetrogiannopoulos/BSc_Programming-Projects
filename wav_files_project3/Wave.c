/*
Petrogiannopoulos Georgios

*/ 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

FILE *fp;
FILE *fp2;
wav_file wf;

int main(int argc , char* argv[])
{
    FILE *fp = NULL;
    
    Wav wav;
    RIFF_t riff;
    FMT_t fmt;
    Data_t data;
    int error = 0;

    if(( strcmp( argv[1] , "-list" )) == 0 )
    {
        fp = fopen(argv[2], "rb");
        if (!fp) 
        {
            printf("can't open audio file\n");
            exit(1);
        }
    
        fread(&wav, 1, sizeof(wav), fp);
        
        riff = wav.riff;
        fmt = wav.fmt;
        data = wav.data;
    
        printf("\nRIFF_CHUNK_HEADER\n====================\n");
        printf("ChunkID \t%c%c%c%c\n", riff.ChunkID[0], riff.ChunkID[1], riff.ChunkID[2], riff.ChunkID[3]);
        printf("ChunkSize \t%d\n", riff.ChunkSize);
        printf("Format \t\t%c%c%c%c\n", riff.Format[0], riff.Format[1], riff.Format[2], riff.Format[3]);
        
        printf("\n");
        
        printf("FMT_SUBCHUNK_HEADER\n====================\n");
        printf("Subchunk1ID \t%c%c%c%c\n", fmt.Subchunk1ID[0], fmt.Subchunk1ID[1], fmt.Subchunk1ID[2], fmt.Subchunk1ID[3]);
        printf("Subchunk1Size \t%d\n", fmt.Subchunk1Size);
        printf("AudioFormat \t%d\n", fmt.AudioFormat);
        printf("NumChannels \t%d\n", fmt.NumChannels);
        printf("SampleRate \t%d\n", fmt.SampleRate);
        printf("ByteRate \t%d\n", fmt.ByteRate);
        printf("BlockAlign \t%d\n", fmt.BlockAlign);
        printf("BitsPerSample \t%d\n", fmt.BitsPerSample);
        
        printf("\n");
    
        printf("DATA_SUBCHUNK_HEADER\n====================\n");

        printf("blockID: %c%c%c%c\n", data.Subchunk2ID[0], data.Subchunk2ID[1], data.Subchunk2ID[2], data.Subchunk2ID[3]);
        printf("blockSize: %d\n", data.Subchunk2Size);
        
        printf("\n");
        
        printf("duration \t%d\n", data.Subchunk2Size / fmt.ByteRate);
    }
    else
    {
        error++;
    }

    if(( strcmp( argv[1] , "-reverse" )) == 0 )
    {
            fp = fopen(argv[2], "rb");
            if (!fp) 
            {
                printf("can't open audio file\n");
                exit(1);
            }
            /** buffer to hold the contents of a file */
            char* buffer;
            
            /** buffer to hold the reverse contents of file */
            char* reverse;

            /** wav struct */
            wav_file *wav;

            /** size of read_file and write_file */
            size_t rval, wval;

            // read file that passed from the command line 
            rval = read_file(argv[2], &buffer);

            // parse the contents of the file into a wav struct
            wav = parse(buffer);
            
            // malloc reverse buffer
            reverse = malloc(rval);

            // copy header of buffer to reverse
            for(int i=0; i<44; i++) 
            {
                reverse[i] = buffer[i];
            }

            int samp = wav->bits_per_samp / 8;
            int size = rval;

            // reverse contents
            for (int i=size; i >= 44; i-=samp)
            {
                for(int j=0; j<=1; j++)
                {
                    if((i-j)>43)
                    {
                        reverse[size-(i-j)+44] = buffer[i-j];
                    }
                }
            }   
            
            // write the reversed contents to second filename from the command line
            wval = write_file(argv[3], reverse, rval);
                
            // output 
            printf("File: %s\n", argv[1]);
            printf("===============================================\n");
            printf("File size is %zu. Read %d bytes.\n", rval, wav->chunk_size);
            printf("Format is '%.*s' with format data length %d.\n", 4, wav->fmt, wav->fmt_length);
            printf("Format type is '%.*s'.\n", 4, wav->wave);
            printf("%d channels with sample rate of %d.\n", wav->num_channels, wav->sample_rate);
            printf("%d byte rate, %d alignment, %d bits per sample\n", wav->bits_per_samp, wav->block_alignment, wav->bits_per_sample);
            printf("Data is '%.*s' and data size is %d\n", 4, wav->beg_data, wav->size_data); 

            // free buffers
            free(buffer);
            free(reverse);

    }
    else
    {
        error++;
    }

    if(( strcmp( argv[1] , "-mono" )) == 0 )
    {
        
        FILE *myFile;
        
         myFile = fopen(argv[2],"rb");
         if (!myFile) 
         {
            printf("can't open audio file\n");
            exit(1);
         }
    
            fread( riff.ChunkID,sizeof(riff.ChunkID),1,myFile);
            fread(&riff.ChunkSize,sizeof(riff.ChunkSize),1,myFile);
            fread( riff.Format,sizeof(riff.Format),1,myFile);
            fread( fmt.Subchunk1ID,sizeof(fmt.Subchunk1ID),1,myFile);
            fread( &fmt.Subchunk1Size,sizeof(fmt.Subchunk1Size),1,myFile);
            fread( &fmt.AudioFormat,sizeof(fmt.AudioFormat),1,myFile);
            fread( &fmt.NumChannels,sizeof(fmt.NumChannels),1,myFile);
            fread( &fmt.SampleRate,sizeof(fmt.SampleRate),1,myFile);
            fread( &fmt.ByteRate,sizeof(fmt.ByteRate),1,myFile);
            fread( &fmt.BlockAlign,sizeof(fmt.BlockAlign),1,myFile);
            fread( &fmt.BitsPerSample,sizeof(fmt.BitsPerSample),1,myFile);
            fread( data.Subchunk2ID,sizeof(data.Subchunk2ID),1,myFile);
            fread( &data.Subchunk2Size,sizeof(data.Subchunk2Size),1,myFile);

        int samples = (riff.ChunkSize*8)/(fmt.NumChannels*fmt.BitsPerSample);

        char **newmono = (char**)malloc(sizeof(char*)*samples);
        int i;
        for(i=0;i<samples;i++)
        {
          newmono[i]=(char*)malloc(sizeof(char)*fmt.BlockAlign);
        }

        for(i=0;i<samples;i++)
        {
          fread(newmono[i],sizeof(char)*fmt.BlockAlign,1,myFile);
        }

        fclose(myFile);

        FILE *myFile2;
        myFile2=fopen(argv[3],"wb");

           /*metatropi apo stereo se mono */
           fmt.NumChannels = 1;
           data.Subchunk2Size /= 2;
           riff.ChunkSize = data.Subchunk2Size + 36;
           fmt.ByteRate /= 2;
           fmt.BlockAlign /= 2;
           /* --------------------------- */

            fwrite( riff.ChunkID,sizeof(riff.ChunkID),1,myFile2);
            fwrite( &riff.ChunkSize,sizeof(riff.ChunkSize),1,myFile2);
            fwrite( riff.Format,sizeof(riff.Format),1,myFile2);
            fwrite( fmt.Subchunk1ID,sizeof(fmt.Subchunk1ID),1,myFile2);
            fwrite( &fmt.Subchunk1Size,sizeof(fmt.Subchunk1Size),1,myFile2);
            fwrite( &fmt.AudioFormat,sizeof(fmt.AudioFormat),1,myFile2);
            fwrite( &fmt.NumChannels,sizeof(fmt.NumChannels),1,myFile2);
            fwrite( &fmt.SampleRate,sizeof(fmt.SampleRate),1,myFile2);
            fwrite( &fmt.ByteRate,sizeof(fmt.ByteRate),1,myFile2);
            fwrite( &fmt.BlockAlign,sizeof(fmt.BlockAlign),1,myFile2);
            fwrite( &fmt.BitsPerSample,sizeof(fmt.BitsPerSample),1,myFile2);
            fwrite( data.Subchunk2ID,sizeof(data.Subchunk2ID),1,myFile2);
            fwrite( &data.Subchunk2Size,sizeof(data.Subchunk2Size),1,myFile2);

        char **newmono2 = (char**)malloc(sizeof(char*)*samples);
        for(i=0;i<samples;i++)
        {
          newmono2[i]=(char*)malloc(sizeof(char)*fmt.BlockAlign);
        }

        int bytes = 45;
        int count = 0;
        
        for(i = 0 ; i < samples; i++)
        {
          
            newmono2[count] = newmono[i];
            count++;
          
          bytes += fmt.BlockAlign;
        }

        for(i=0;i<count;i++)
        {
          fwrite(newmono2[i], sizeof(char)*fmt.BlockAlign, 1, myFile2);
        }
        free(newmono);
        free(newmono2);

        printf("\nRIFF_CHUNK_HEADER\n====================\n");
        printf("ChunkID \t%c%c%c%c\n", riff.ChunkID[0], riff.ChunkID[1], riff.ChunkID[2], riff.ChunkID[3]);
        printf("ChunkSize \t%d\n", riff.ChunkSize);
        printf("Format \t\t%c%c%c%c\n", riff.Format[0], riff.Format[1], riff.Format[2], riff.Format[3]);
        printf("\n");
        
        printf("FMT_SUBCHUNK_HEADER\n====================\n");
        printf("Subchunk1ID \t%c%c%c%c\n", fmt.Subchunk1ID[0], fmt.Subchunk1ID[1], fmt.Subchunk1ID[2], fmt.Subchunk1ID[3]);
        printf("Subchunk1Size \t%d\n", fmt.Subchunk1Size);
        printf("AudioFormat \t%d\n", fmt.AudioFormat);
        printf("NumChannels \t%d\n", fmt.NumChannels);
        printf("SampleRate \t%d\n", fmt.SampleRate);
        printf("ByteRate \t%d\n", fmt.ByteRate);
        printf("BlockAlign \t%d\n", fmt.BlockAlign);
        printf("BitsPerSample \t%d\n", fmt.BitsPerSample);
        
        printf("\n");
    
        printf("DATA_SUBCHUNK_HEADER\n====================\n");

        printf("blockID: %c%c%c%c\n", data.Subchunk2ID[0], data.Subchunk2ID[1], data.Subchunk2ID[2], data.Subchunk2ID[3]);
        printf("blockSize: %d\n", data.Subchunk2Size);
        
        printf("\n");
        
        printf("duration \t%d\n", data.Subchunk2Size / fmt.ByteRate);
    }
    else
    {
        error++;
    }

    if(( strcmp( argv[1] , "-crop" )) == 0 )
    {
        /* ENALLAKTIKI LISI 
            ME XRISI : ffmpeg (package) audio converter for linux */
        /*       
        system("sudo apt install ffmpeg");
        int first = atoi(argv[3]);
        int second = atoi(argv[4]);
        char command[100];
        sprintf(command, "ffmpeg -ss %d -i %s -t %d -c copy -y %s", first , argv[2] , second , argv[5] );
        system(command);
        */

        fp = fopen(argv[2], "rb");
        if (!fp) 
        {
            printf("can't open audio file\n");
            exit(1);
        }
    
        fread(&wav, 1, sizeof(wav), fp);
        
        riff = wav.riff;
        fmt = wav.fmt;
        data = wav.data;
    
        if( (atoi(argv[3])>=atoi(argv[4])) || (atoi(argv[3])<0) || (atoi(argv[4])>data.Subchunk2Size / fmt.ByteRate ) )
        {
            printf("true\n");
            goto label;
        }   
       
        int bytesmin,bytesmax;
        FILE *myFile;
        myFile = fopen(argv[2],"rb");

            fread( riff.ChunkID,sizeof(riff.ChunkID),1,myFile);
            fread(&riff.ChunkSize,sizeof(riff.ChunkSize),1,myFile);
            fread( riff.Format,sizeof(riff.Format),1,myFile);
            fread( fmt.Subchunk1ID,sizeof(fmt.Subchunk1ID),1,myFile);
            fread( &fmt.Subchunk1Size,sizeof(fmt.Subchunk1Size),1,myFile);
            fread( &fmt.AudioFormat,sizeof(fmt.AudioFormat),1,myFile);
            fread( &fmt.NumChannels,sizeof(fmt.NumChannels),1,myFile);
            fread( &fmt.SampleRate,sizeof(fmt.SampleRate),1,myFile);
            fread( &fmt.ByteRate,sizeof(fmt.ByteRate),1,myFile);
            fread( &fmt.BlockAlign,sizeof(fmt.BlockAlign),1,myFile);
            fread( &fmt.BitsPerSample,sizeof(fmt.BitsPerSample),1,myFile);
            fread( data.Subchunk2ID,sizeof(data.Subchunk2ID),1,myFile);
            fread( &data.Subchunk2Size,sizeof(data.Subchunk2Size),1,myFile);

        int samples = (riff.ChunkSize*8)/(fmt.NumChannels*fmt.BitsPerSample);

        char **newsound = (char**)malloc(sizeof(char*)*samples);

        int i;
        for(i=0;i<samples;i++)
        {
          newsound[i]=(char*)malloc(sizeof(char)*fmt.BlockAlign);
        }

        for(i=0;i<samples;i++)
        {
          fread(newsound[i],sizeof(char)*fmt.BlockAlign,1,myFile);
        }

        fclose(myFile);

        FILE *myFile2;
        myFile2=fopen(argv[5],"wb");

            fwrite( riff.ChunkID,sizeof(riff.ChunkID),1,myFile2);
            fwrite( &riff.ChunkSize,sizeof(riff.ChunkSize),1,myFile2);
            fwrite( riff.Format,sizeof(riff.Format),1,myFile2);
            fwrite( fmt.Subchunk1ID,sizeof(fmt.Subchunk1ID),1,myFile2);
            fwrite( &fmt.Subchunk1Size,sizeof(fmt.Subchunk1Size),1,myFile2);
            fwrite( &fmt.AudioFormat,sizeof(fmt.AudioFormat),1,myFile2);
            fwrite( &fmt.NumChannels,sizeof(fmt.NumChannels),1,myFile2);
            fwrite( &fmt.SampleRate,sizeof(fmt.SampleRate),1,myFile2);
            fwrite( &fmt.ByteRate,sizeof(fmt.ByteRate),1,myFile2);
            fwrite( &fmt.BlockAlign,sizeof(fmt.BlockAlign),1,myFile2);
            fwrite( &fmt.BitsPerSample,sizeof(fmt.BitsPerSample),1,myFile2);
            fwrite( data.Subchunk2ID,sizeof(data.Subchunk2ID),1,myFile2);
            fwrite( &data.Subchunk2Size,sizeof(data.Subchunk2Size),1,myFile2);

        char **newsound2 = (char**)malloc(sizeof(char*)*samples);

        for(i=0;i<samples;i++)
        {
          newsound2[i]=(char*)malloc(sizeof(char)*fmt.BlockAlign);
        }

        bytesmin = (fmt.NumChannels*fmt.SampleRate*fmt.BitsPerSample/8)*atoi(argv[3]);
        bytesmax = (fmt.NumChannels*fmt.SampleRate*fmt.BitsPerSample/8)*atoi(argv[4]);
        int bytes = 45;
        int count = 0;
        
        for(i = 0 ; i < samples; i++)
        {
          if( bytes >= bytesmin && bytes <= bytesmax)
          {
            newsound2[count] = newsound[i];
            count++;
          }
          bytes += fmt.BlockAlign;
        }

        for(i=0;i<count;i++)
        {
          fwrite(newsound2[i], sizeof(char)*fmt.BlockAlign, 1, myFile2);
        }
        free(newsound);
        free(newsound2);
    }
    else
    {
        error++;
    }

    if(error==4)
    {
        label:
        printf("wrong command syntax!\n");
        printf("commands syntax:\n");
        printf("> for file info type : ./wave -list input.wav\n");
        printf("> for reversing type : ./wave -reverse input.wav output.wav\n");
        printf("> for converting to mono type : ./wave -mono input.wav output.wav\n");
        printf("> for crop type: ./wave -crop input.wav start_number end_number output.wav\n");
    }

 }

