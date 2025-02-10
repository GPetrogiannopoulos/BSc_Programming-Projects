
/* for extraxting details of the wav file */

typedef struct WAV_RIFF 
{
    /* chunk "riff" */
    char ChunkID[4];   /* "RIFF" */
    /* sub-chunk-size */
    uint32_t ChunkSize; /* 36 + Subchunk2Size */
    /* sub-chunk-data */
    char Format[4];    /* "WAVE" */
} RIFF_t;

typedef struct WAV_FMT 
{
    /* sub-chunk "fmt" */
    char Subchunk1ID[4];   /* "fmt " */
    /* sub-chunk-size */
    uint32_t Subchunk1Size; /* 16 for PCM */
    /* sub-chunk-data */
    uint16_t AudioFormat;   /* PCM = 1*/
    uint16_t NumChannels;   /* Mono = 1, Stereo = 2, etc. */
    uint32_t SampleRate;    /* 8000, 44100, etc. */
    uint32_t ByteRate;  /* = SampleRate * NumChannels * BitsPerSample/8 */
    uint16_t BlockAlign;    /* = NumChannels * BitsPerSample/8 */
    uint16_t BitsPerSample; /* 8bits, 16bits, etc. */
} FMT_t;

typedef struct WAV_data 
{
    /* sub-chunk "data" */
    char Subchunk2ID[4];   /* "data" */
    /* sub-chunk-size */
    uint32_t Subchunk2Size; /* data size */
    /* sub-chunk-data */
//    Data_block_t block;
} Data_t;

//typedef struct WAV_data_block {
//} Data_block_t;

typedef struct WAV_foρmat 
{
   RIFF_t riff;
   FMT_t fmt;
   Data_t data;
} Wav;
/*--------------------------------------------------------*/

/* for the reverse */
size_t read_file(char* filename, char **buffer);
size_t write_file(char* filename, char *buffer, size_t size);

typedef struct wav_file
{
    char beg[4];
    int chunk_size;
    char wave[4];
    char fmt[4];
    int fmt_length;
    short fmt_type;
    short num_channels;
    int sample_rate;
    int bits_per_sample;
    short block_alignment;
    short bits_per_samp;
    char beg_data[4];
    int size_data;
    char* act_data; 
} wav_file;

wav_file* parse(char* contents);

FILE *fp;
wav_file wf;
/************************************************
Reads the file that is passed in and mallocs 
the buffer to the size of the file. The contents 
of the file is then read into the buffer.
@param filename the name of the file
@param buffer the address of the buffer
@return size the size of file 
************************************************/
size_t read_file(char* filename, char** buffer) 
{
 
    // open file
    fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);  /* moves file position to the end of the file */
    size_t size = ftell(fp); /* current file position */
    fseek(fp, 0, SEEK_SET);  /* moves file position to the start of the file */

    // malloc buffer to size of file
    *buffer = malloc(size);
 
    // read file into buffer
    fread(*buffer, sizeof(char), size, fp);

    // check if there is an error reading file 
    if(ferror(fp))
    {
        printf("Error reading: %s/n", filename);
    }
 
    // check if end of the file has been reached
    if(feof(fp)) 
    {
        printf("End of file reached./n");
    }

    // close file
    fclose(fp);

    return size;
}

/************************************************
Writes a file to system 
@param filename the name of the file
@param buffer the contents of the file
@param size the size of the file
@return size of written file
************************************************/
size_t write_file(char* filename, char* buffer, size_t size) 
{

    // open file
    fp = fopen(filename, "wb");
    fseek(fp, 0, SEEK_END);
    fseek(fp, 0, SEEK_SET);

    // write file to system
    size_t s = fwrite(buffer, sizeof(char), size, fp);

    // check if there was an error writing to file
    if(ferror(fp)) 
    {
        printf("Error writing to file: %s/n", filename);
    }

    // close file
    fclose(fp);

    return s;
}   

/***********************************************
Parses a file into a wav file. The contents of
the file get saved into a wav struct.
@param contents the contents of the file
@return a pointer to the wav file
************************************************/
wav_file* parse(char* contents) 
{
    // copy the contents of the file into a wav struct
    memcpy(&wf, contents, sizeof(struct wav_file));
    
    return &wf;
}