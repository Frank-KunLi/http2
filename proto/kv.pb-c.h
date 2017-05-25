/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: kv.proto */

#ifndef PROTOBUF_C_kv_2eproto__INCLUDED
#define PROTOBUF_C_kv_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1001001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Mvccpb__KeyValue Mvccpb__KeyValue;
typedef struct _Mvccpb__Event Mvccpb__Event;


/* --- enums --- */

typedef enum _Mvccpb__Event__EventType {
  MVCCPB__EVENT__EVENT_TYPE__PUT = 0,
  MVCCPB__EVENT__EVENT_TYPE__DELETE = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MVCCPB__EVENT__EVENT_TYPE)
} Mvccpb__Event__EventType;

/* --- messages --- */

struct  _Mvccpb__KeyValue
{
  ProtobufCMessage base;
  /*
   * key is the key in bytes. An empty key is not allowed.
   */
  protobuf_c_boolean has_key;
  ProtobufCBinaryData key;
  /*
   * create_revision is the revision of last creation on this key.
   */
  protobuf_c_boolean has_create_revision;
  int64_t create_revision;
  /*
   * mod_revision is the revision of last modification on this key.
   */
  protobuf_c_boolean has_mod_revision;
  int64_t mod_revision;
  /*
   * version is the version of the key. A deletion resets
   * the version to zero and any modification of the key
   * increases its version.
   */
  protobuf_c_boolean has_version;
  int64_t version;
  /*
   * value is the value held by the key, in bytes.
   */
  protobuf_c_boolean has_value;
  ProtobufCBinaryData value;
  /*
   * lease is the ID of the lease that attached to key.
   * When the attached lease expires, the key will be deleted.
   * If lease is 0, then no lease is attached to the key.
   */
  protobuf_c_boolean has_lease;
  int64_t lease;
};
#define MVCCPB__KEY_VALUE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&mvccpb__key_value__descriptor) \
    , 0,{0,NULL}, 0,0, 0,0, 0,0, 0,{0,NULL}, 0,0 }


struct  _Mvccpb__Event
{
  ProtobufCMessage base;
  /*
   * type is the kind of event. If type is a PUT, it indicates
   * new data has been stored to the key. If type is a DELETE,
   * it indicates the key was deleted.
   */
  protobuf_c_boolean has_type;
  Mvccpb__Event__EventType type;
  /*
   * kv holds the KeyValue for the event.
   * A PUT event contains current kv pair.
   * A PUT event with kv.Version=1 indicates the creation of a key.
   * A DELETE/EXPIRE event contains the deleted key with
   * its modification revision set to the revision of deletion.
   */
  Mvccpb__KeyValue *kv;
};
#define MVCCPB__EVENT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&mvccpb__event__descriptor) \
    , 0,0, NULL }


/* Mvccpb__KeyValue methods */
void   mvccpb__key_value__init
                     (Mvccpb__KeyValue         *message);
size_t mvccpb__key_value__get_packed_size
                     (const Mvccpb__KeyValue   *message);
size_t mvccpb__key_value__pack
                     (const Mvccpb__KeyValue   *message,
                      uint8_t             *out);
size_t mvccpb__key_value__pack_to_buffer
                     (const Mvccpb__KeyValue   *message,
                      ProtobufCBuffer     *buffer);
Mvccpb__KeyValue *
       mvccpb__key_value__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   mvccpb__key_value__free_unpacked
                     (Mvccpb__KeyValue *message,
                      ProtobufCAllocator *allocator);
/* Mvccpb__Event methods */
void   mvccpb__event__init
                     (Mvccpb__Event         *message);
size_t mvccpb__event__get_packed_size
                     (const Mvccpb__Event   *message);
size_t mvccpb__event__pack
                     (const Mvccpb__Event   *message,
                      uint8_t             *out);
size_t mvccpb__event__pack_to_buffer
                     (const Mvccpb__Event   *message,
                      ProtobufCBuffer     *buffer);
Mvccpb__Event *
       mvccpb__event__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   mvccpb__event__free_unpacked
                     (Mvccpb__Event *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Mvccpb__KeyValue_Closure)
                 (const Mvccpb__KeyValue *message,
                  void *closure_data);
typedef void (*Mvccpb__Event_Closure)
                 (const Mvccpb__Event *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor mvccpb__key_value__descriptor;
extern const ProtobufCMessageDescriptor mvccpb__event__descriptor;
extern const ProtobufCEnumDescriptor    mvccpb__event__event_type__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_kv_2eproto__INCLUDED */