#ifndef __HTTP2_FRAME_H
 #define __HTTP2_FRAME_H

#include "common.h"
 
#define SETTINGS_MAX_FRAME_SIZE     (16777215) //2^24
#define MINIMUM_FRAME_SIZE          9
enum HTTP2_FRAME_TYPE{
  HTTP2_FRAME_DATA          = 0x0,
  HTTP2_FRAME_HEADES        = 0x1,
  HTTP2_FRAME_PRIORITY      = 0x2,
  HTTP2_FRAME_RST_STREAM    = 0x3,
  HTTP2_FRAME_SETTINGS      = 0x4,
  HTTP2_FRAME_PUSH_PROMISE  = 0x5,            
  HTTP2_FRAME_PING          = 0x6,
  HTTP2_FRAME_GOAWAY        = 0x7,
  HTTP2_FRAME_WINDOW_UPDATE = 0x8,
  HTTP2_FRAME_CONTINUATION  = 0x9,
};
 
enum HTTP2_RETURN_ERROR_CODES{
    HTTP2_RETURN_NO_ERROR               = 0x0,
    HTTP2_RETURN_PROTOCOL_ERROR         = 0x1,
    HTTP2_RETURN_INTERNAL_ERROR         = 0x2,
    HTTP2_RETURN_FLOW_CONTROL_ERROR     = 0x3,
    HTTP2_RETURN_SETTINGS_TIMEOUT       = 0x4,
    HTTP2_RETURN_STREAM_CLOSED          = 0x5,
    HTTP2_RETURN_FRAME_SIZE_ERROR       = 0x6,
    HTTP2_RETURN_REFUSED_STREAM         = 0x7,
    HTTP2_RETURN_CANCEL                 = 0x8,
    HTTP2_RETURN_COMPRESSION_ERROR      = 0x9,
    HTTP2_RETURN_CONNECT_ERROR          = 0xa,
    HTTP2_RETURN_ENHANCE_YOUR_CALM      = 0xb,
    HTTP2_RETURN_INADEQUATE_SECURITY    = 0xc,
    HTTP2_RETURN_HTTP_1_1_REQUIRED      = 0xd,
    
    HTTP2_RETURN_NEED_MORE_DATA         = 100,
    
    HTTP2_RETURN_INVALID_FRAME_TYPE     = -100,
    HTTP2_RETURN_UNIMPLEMENTED          = -200,
    HTTP2_RETURN_NULL_POINTER           = -201,
    HTTP2_RETURN_ERROR_MEMORY           = -202,
};

typedef struct _buffer_t HTTP2_FRAME_BUFFER;

typedef struct HTTP2_PLAYLOAD_DATA{
    int padding_length;             //8 bits  
    void *data;                     //Application data
    void *padding;                  //
}HTTP2_PLAYLOAD_DATA;

typedef struct HTTP2_PLOYLOAD_HEADERS{
    int padding_length;             //8 bits  
    int is_exclusive;               //
    void *padding;                  //
    unsigned int stream_dependency; //
    int weigth;                     //8 bits
    void *header_block_fragment;    //header data
}HTTP2_PLOYLOAD_HEADERS;

typedef struct HTTP2_PLAYLOAD_PRIORITY{
    int is_exclusive;
    unsigned int stream_dependency;
    int weigth;
}HTTP2_PLAYLOAD_PRIORITY;

typedef struct HTTP2_PLAYLOAD_WINDOW_UPDATE{
    int reserved;
    unsigned int window_size_increment;  
}HTTP2_PLAYLOAD_WINDOW_UPDATE;

typedef struct HTTP2_PLAYLOAD_SETTINGS{
    int id;
    unsigned int value;
}HTTP2_PLAYLOAD_SETTINGS;

/*typedef struct HTTP2_FRAME_FORMAT{
    struct HTTP2_FRAME_FORMAT *next;
    struct HTTP2_FRAME_FORMAT *prev;
    unsigned int length;            //24 bits
    int type;                       //8 bits
    int flags;                      //8 bits
    int reserved;                    //1 bits
    unsigned int streamID;          //31 bits
    union {
        HTTP2_PLAYLOAD_DATA             *data_playload;
        HTTP2_PLOYLOAD_HEADERS          *headers_playload;
        HTTP2_PLAYLOAD_PRIORITY         *priority_playload;
        HTTP2_PLAYLOAD_WINDOW_UPDATE    *update_playload;
        HTTP2_PLAYLOAD_SETTINGS         *settings_playload;
    };
    void * playload;
}HTTP2_FRAME_FORMAT;

typedef struct HTTP2_FRAME_FLAG{
    union {
        struct
        {
            unsigned int end_stream     : 1;
            unsigned int unused_1_2     : 2;
            unsigned int padded         : 1;
            unsigned int unused_4_15    : 12;
        }frame_data;

        struct
        {
            unsigned int end_stream     : 1;
            unsigned int unused_1       : 1;
            unsigned int end_header     : 1;
            unsigned int padded         : 1;
            unsigned int unused_4_15    : 12;
        }frame_headers;

        struct
        {
            unsigned int unused_0_15    : 16;
        }frame_priority;

        struct
        {
            unsigned int unused_0_15    : 16;
        }frame_window_update;

        struct
        {
            unsigned int ack            : 1;
            unsigned int unused_1_15    : 15;
        }frame_settings;

        unsigned int value;
    };
}HTTP2_FRAME_FLAG;*/

typedef struct HTTP2_FRAME_FORMAT{
    struct HTTP2_FRAME_FORMAT *next;
    struct HTTP2_FRAME_FORMAT *prev;
    unsigned int length;            //24 bits
    int type;                       //8 bits
    // int flags;                      //8 bits
    union {
        struct
        {
            unsigned int end_stream     : 1;
            unsigned int unused_1_2     : 2;
            unsigned int padded         : 1;
            unsigned int unused_4_15    : 12;
        }frame_data_flags;

        struct
        {
            unsigned int end_stream     : 1;
            unsigned int unused_1       : 1;
            unsigned int end_header     : 1;
            unsigned int padded         : 1;
            unsigned int unused_4_15    : 12;
        }frame_headers_flags;

        struct
        {
            unsigned int unused_0_15    : 16;
        }frame_priority_flags;

        struct
        {
            unsigned int unused_0_15    : 16;
        }frame_window_update_flags;

        struct
        {
            unsigned int ack            : 1;
            unsigned int unused_1_15    : 15;
        }frame_settings_flags;

        unsigned int flags;
    };
    int reserved;                    //1 bits
    unsigned int streamID;          //31 bits
    union {
        HTTP2_PLAYLOAD_DATA             *data_playload;
        HTTP2_PLOYLOAD_HEADERS          *headers_playload;
        HTTP2_PLAYLOAD_PRIORITY         *priority_playload;
        HTTP2_PLAYLOAD_WINDOW_UPDATE    *update_playload;
        HTTP2_PLAYLOAD_SETTINGS         *settings_playload;
    };
    void * playload;
}HTTP2_FRAME_FORMAT;


HTTP2_FRAME_FORMAT * HTTP2_frame_create();
int HTTP2_frame_decode(HTTP2_FRAME_BUFFER *buffer, HTTP2_FRAME_FORMAT **frame, char *error);
void * HTTP2_playload_create(int ftype);
int HTTP2_playload_decode(HTTP2_FRAME_BUFFER *buffer, HTTP2_FRAME_FORMAT *frame, char *error);
int HTTP2_FRAME_add_playload(HTTP2_FRAME_FORMAT **frame, int type, void *playload, unsigned int streamID);
int HTTP2_FRAME_FREE( HTTP2_FRAME_FORMAT *frame );
int HTTP2_PLAYLOAD_FREE( HTTP2_FRAME_FORMAT *frame );

#endif 
