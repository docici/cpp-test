/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: paxos_msg.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "paxos_msg.pb-c.h"
void   xh__header__init
                     (Xh__Header         *message)
{
  static Xh__Header init_value = XH__HEADER__INIT;
  *message = init_value;
}
size_t xh__header__get_packed_size
                     (const Xh__Header *message)
{
  assert(message->base.descriptor == &xh__header__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t xh__header__pack
                     (const Xh__Header *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &xh__header__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t xh__header__pack_to_buffer
                     (const Xh__Header *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &xh__header__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Xh__Header *
       xh__header__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Xh__Header *)
     protobuf_c_message_unpack (&xh__header__descriptor,
                                allocator, len, data);
}
void   xh__header__free_unpacked
                     (Xh__Header *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &xh__header__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   xh__paxos_msg__init
                     (Xh__PaxosMsg         *message)
{
  static Xh__PaxosMsg init_value = XH__PAXOS_MSG__INIT;
  *message = init_value;
}
size_t xh__paxos_msg__get_packed_size
                     (const Xh__PaxosMsg *message)
{
  assert(message->base.descriptor == &xh__paxos_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t xh__paxos_msg__pack
                     (const Xh__PaxosMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &xh__paxos_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t xh__paxos_msg__pack_to_buffer
                     (const Xh__PaxosMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &xh__paxos_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Xh__PaxosMsg *
       xh__paxos_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Xh__PaxosMsg *)
     protobuf_c_message_unpack (&xh__paxos_msg__descriptor,
                                allocator, len, data);
}
void   xh__paxos_msg__free_unpacked
                     (Xh__PaxosMsg *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &xh__paxos_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   xh__checkpoint_msg__init
                     (Xh__CheckpointMsg         *message)
{
  static Xh__CheckpointMsg init_value = XH__CHECKPOINT_MSG__INIT;
  *message = init_value;
}
size_t xh__checkpoint_msg__get_packed_size
                     (const Xh__CheckpointMsg *message)
{
  assert(message->base.descriptor == &xh__checkpoint_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t xh__checkpoint_msg__pack
                     (const Xh__CheckpointMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &xh__checkpoint_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t xh__checkpoint_msg__pack_to_buffer
                     (const Xh__CheckpointMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &xh__checkpoint_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Xh__CheckpointMsg *
       xh__checkpoint_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Xh__CheckpointMsg *)
     protobuf_c_message_unpack (&xh__checkpoint_msg__descriptor,
                                allocator, len, data);
}
void   xh__checkpoint_msg__free_unpacked
                     (Xh__CheckpointMsg *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &xh__checkpoint_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   xh__acceptor_state_data__init
                     (Xh__AcceptorStateData         *message)
{
  static Xh__AcceptorStateData init_value = XH__ACCEPTOR_STATE_DATA__INIT;
  *message = init_value;
}
size_t xh__acceptor_state_data__get_packed_size
                     (const Xh__AcceptorStateData *message)
{
  assert(message->base.descriptor == &xh__acceptor_state_data__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t xh__acceptor_state_data__pack
                     (const Xh__AcceptorStateData *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &xh__acceptor_state_data__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t xh__acceptor_state_data__pack_to_buffer
                     (const Xh__AcceptorStateData *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &xh__acceptor_state_data__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Xh__AcceptorStateData *
       xh__acceptor_state_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Xh__AcceptorStateData *)
     protobuf_c_message_unpack (&xh__acceptor_state_data__descriptor,
                                allocator, len, data);
}
void   xh__acceptor_state_data__free_unpacked
                     (Xh__AcceptorStateData *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &xh__acceptor_state_data__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   xh__paxos_node_info__init
                     (Xh__PaxosNodeInfo         *message)
{
  static Xh__PaxosNodeInfo init_value = XH__PAXOS_NODE_INFO__INIT;
  *message = init_value;
}
size_t xh__paxos_node_info__get_packed_size
                     (const Xh__PaxosNodeInfo *message)
{
  assert(message->base.descriptor == &xh__paxos_node_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t xh__paxos_node_info__pack
                     (const Xh__PaxosNodeInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &xh__paxos_node_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t xh__paxos_node_info__pack_to_buffer
                     (const Xh__PaxosNodeInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &xh__paxos_node_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Xh__PaxosNodeInfo *
       xh__paxos_node_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Xh__PaxosNodeInfo *)
     protobuf_c_message_unpack (&xh__paxos_node_info__descriptor,
                                allocator, len, data);
}
void   xh__paxos_node_info__free_unpacked
                     (Xh__PaxosNodeInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &xh__paxos_node_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   xh__system_variables__init
                     (Xh__SystemVariables         *message)
{
  static Xh__SystemVariables init_value = XH__SYSTEM_VARIABLES__INIT;
  *message = init_value;
}
size_t xh__system_variables__get_packed_size
                     (const Xh__SystemVariables *message)
{
  assert(message->base.descriptor == &xh__system_variables__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t xh__system_variables__pack
                     (const Xh__SystemVariables *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &xh__system_variables__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t xh__system_variables__pack_to_buffer
                     (const Xh__SystemVariables *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &xh__system_variables__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Xh__SystemVariables *
       xh__system_variables__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Xh__SystemVariables *)
     protobuf_c_message_unpack (&xh__system_variables__descriptor,
                                allocator, len, data);
}
void   xh__system_variables__free_unpacked
                     (Xh__SystemVariables *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &xh__system_variables__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   xh__master_variables__init
                     (Xh__MasterVariables         *message)
{
  static Xh__MasterVariables init_value = XH__MASTER_VARIABLES__INIT;
  *message = init_value;
}
size_t xh__master_variables__get_packed_size
                     (const Xh__MasterVariables *message)
{
  assert(message->base.descriptor == &xh__master_variables__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t xh__master_variables__pack
                     (const Xh__MasterVariables *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &xh__master_variables__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t xh__master_variables__pack_to_buffer
                     (const Xh__MasterVariables *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &xh__master_variables__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Xh__MasterVariables *
       xh__master_variables__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Xh__MasterVariables *)
     protobuf_c_message_unpack (&xh__master_variables__descriptor,
                                allocator, len, data);
}
void   xh__master_variables__free_unpacked
                     (Xh__MasterVariables *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &xh__master_variables__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   xh__paxos_value__init
                     (Xh__PaxosValue         *message)
{
  static Xh__PaxosValue init_value = XH__PAXOS_VALUE__INIT;
  *message = init_value;
}
size_t xh__paxos_value__get_packed_size
                     (const Xh__PaxosValue *message)
{
  assert(message->base.descriptor == &xh__paxos_value__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t xh__paxos_value__pack
                     (const Xh__PaxosValue *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &xh__paxos_value__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t xh__paxos_value__pack_to_buffer
                     (const Xh__PaxosValue *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &xh__paxos_value__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Xh__PaxosValue *
       xh__paxos_value__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Xh__PaxosValue *)
     protobuf_c_message_unpack (&xh__paxos_value__descriptor,
                                allocator, len, data);
}
void   xh__paxos_value__free_unpacked
                     (Xh__PaxosValue *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &xh__paxos_value__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   xh__batch_paxos_values__init
                     (Xh__BatchPaxosValues         *message)
{
  static Xh__BatchPaxosValues init_value = XH__BATCH_PAXOS_VALUES__INIT;
  *message = init_value;
}
size_t xh__batch_paxos_values__get_packed_size
                     (const Xh__BatchPaxosValues *message)
{
  assert(message->base.descriptor == &xh__batch_paxos_values__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t xh__batch_paxos_values__pack
                     (const Xh__BatchPaxosValues *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &xh__batch_paxos_values__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t xh__batch_paxos_values__pack_to_buffer
                     (const Xh__BatchPaxosValues *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &xh__batch_paxos_values__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Xh__BatchPaxosValues *
       xh__batch_paxos_values__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Xh__BatchPaxosValues *)
     protobuf_c_message_unpack (&xh__batch_paxos_values__descriptor,
                                allocator, len, data);
}
void   xh__batch_paxos_values__free_unpacked
                     (Xh__BatchPaxosValues *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &xh__batch_paxos_values__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor xh__header__field_descriptors[4] =
{
  {
    "gid",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__Header, gid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "rid",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__Header, rid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "cmdid",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Xh__Header, cmdid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "version",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(Xh__Header, has_version),
    offsetof(Xh__Header, version),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned xh__header__field_indices_by_name[] = {
  2,   /* field[2] = cmdid */
  0,   /* field[0] = gid */
  1,   /* field[1] = rid */
  3,   /* field[3] = version */
};
static const ProtobufCIntRange xh__header__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor xh__header__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "xh.Header",
  "Header",
  "Xh__Header",
  "xh",
  sizeof(Xh__Header),
  4,
  xh__header__field_descriptors,
  xh__header__field_indices_by_name,
  1,  xh__header__number_ranges,
  (ProtobufCMessageInit) xh__header__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor xh__paxos_msg__field_descriptors[15] =
{
  {
    "MsgType",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Xh__PaxosMsg, msgtype),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "InstanceID",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__PaxosMsg, has_instanceid),
    offsetof(Xh__PaxosMsg, instanceid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "NodeID",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__PaxosMsg, has_nodeid),
    offsetof(Xh__PaxosMsg, nodeid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ProposalID",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__PaxosMsg, has_proposalid),
    offsetof(Xh__PaxosMsg, proposalid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ProposalNodeID",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__PaxosMsg, has_proposalnodeid),
    offsetof(Xh__PaxosMsg, proposalnodeid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Value",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    offsetof(Xh__PaxosMsg, has_value),
    offsetof(Xh__PaxosMsg, value),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PreAcceptID",
    7,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__PaxosMsg, has_preacceptid),
    offsetof(Xh__PaxosMsg, preacceptid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PreAcceptNodeID",
    8,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__PaxosMsg, has_preacceptnodeid),
    offsetof(Xh__PaxosMsg, preacceptnodeid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "RejectByPromiseID",
    9,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__PaxosMsg, has_rejectbypromiseid),
    offsetof(Xh__PaxosMsg, rejectbypromiseid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "NowInstanceID",
    10,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__PaxosMsg, has_nowinstanceid),
    offsetof(Xh__PaxosMsg, nowinstanceid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "MinChosenInstanceID",
    11,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__PaxosMsg, has_minchoseninstanceid),
    offsetof(Xh__PaxosMsg, minchoseninstanceid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "LastChecksum",
    12,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(Xh__PaxosMsg, has_lastchecksum),
    offsetof(Xh__PaxosMsg, lastchecksum),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Flag",
    13,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(Xh__PaxosMsg, has_flag),
    offsetof(Xh__PaxosMsg, flag),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "SystemVariables",
    14,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    offsetof(Xh__PaxosMsg, has_systemvariables),
    offsetof(Xh__PaxosMsg, systemvariables),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "MasterVariables",
    15,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    offsetof(Xh__PaxosMsg, has_mastervariables),
    offsetof(Xh__PaxosMsg, mastervariables),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned xh__paxos_msg__field_indices_by_name[] = {
  12,   /* field[12] = Flag */
  1,   /* field[1] = InstanceID */
  11,   /* field[11] = LastChecksum */
  14,   /* field[14] = MasterVariables */
  10,   /* field[10] = MinChosenInstanceID */
  0,   /* field[0] = MsgType */
  2,   /* field[2] = NodeID */
  9,   /* field[9] = NowInstanceID */
  6,   /* field[6] = PreAcceptID */
  7,   /* field[7] = PreAcceptNodeID */
  3,   /* field[3] = ProposalID */
  4,   /* field[4] = ProposalNodeID */
  8,   /* field[8] = RejectByPromiseID */
  13,   /* field[13] = SystemVariables */
  5,   /* field[5] = Value */
};
static const ProtobufCIntRange xh__paxos_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 15 }
};
const ProtobufCMessageDescriptor xh__paxos_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "xh.PaxosMsg",
  "PaxosMsg",
  "Xh__PaxosMsg",
  "xh",
  sizeof(Xh__PaxosMsg),
  15,
  xh__paxos_msg__field_descriptors,
  xh__paxos_msg__field_indices_by_name,
  1,  xh__paxos_msg__number_ranges,
  (ProtobufCMessageInit) xh__paxos_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor xh__checkpoint_msg__field_descriptors[11] =
{
  {
    "MsgType",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Xh__CheckpointMsg, msgtype),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "NodeID",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__CheckpointMsg, nodeid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Flag",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(Xh__CheckpointMsg, has_flag),
    offsetof(Xh__CheckpointMsg, flag),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "UUID",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__CheckpointMsg, uuid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Sequence",
    5,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__CheckpointMsg, sequence),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "CheckpointInstanceID",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__CheckpointMsg, has_checkpointinstanceid),
    offsetof(Xh__CheckpointMsg, checkpointinstanceid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Checksum",
    7,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(Xh__CheckpointMsg, has_checksum),
    offsetof(Xh__CheckpointMsg, checksum),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "FilePath",
    8,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Xh__CheckpointMsg, filepath),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "SMID",
    9,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(Xh__CheckpointMsg, has_smid),
    offsetof(Xh__CheckpointMsg, smid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Offset",
    10,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(Xh__CheckpointMsg, has_offset),
    offsetof(Xh__CheckpointMsg, offset),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Buffer",
    11,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BYTES,
    offsetof(Xh__CheckpointMsg, has_buffer),
    offsetof(Xh__CheckpointMsg, buffer),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned xh__checkpoint_msg__field_indices_by_name[] = {
  10,   /* field[10] = Buffer */
  5,   /* field[5] = CheckpointInstanceID */
  6,   /* field[6] = Checksum */
  7,   /* field[7] = FilePath */
  2,   /* field[2] = Flag */
  0,   /* field[0] = MsgType */
  1,   /* field[1] = NodeID */
  9,   /* field[9] = Offset */
  8,   /* field[8] = SMID */
  4,   /* field[4] = Sequence */
  3,   /* field[3] = UUID */
};
static const ProtobufCIntRange xh__checkpoint_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 11 }
};
const ProtobufCMessageDescriptor xh__checkpoint_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "xh.CheckpointMsg",
  "CheckpointMsg",
  "Xh__CheckpointMsg",
  "xh",
  sizeof(Xh__CheckpointMsg),
  11,
  xh__checkpoint_msg__field_descriptors,
  xh__checkpoint_msg__field_indices_by_name,
  1,  xh__checkpoint_msg__number_ranges,
  (ProtobufCMessageInit) xh__checkpoint_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor xh__acceptor_state_data__field_descriptors[7] =
{
  {
    "InstanceID",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__AcceptorStateData, instanceid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PromiseID",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__AcceptorStateData, promiseid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "PromiseNodeID",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__AcceptorStateData, promisenodeid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "AcceptedID",
    4,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__AcceptorStateData, acceptedid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "AcceptedNodeID",
    5,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__AcceptorStateData, acceptednodeid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "AcceptedValue",
    6,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(Xh__AcceptorStateData, acceptedvalue),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Checksum",
    7,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Xh__AcceptorStateData, checksum),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned xh__acceptor_state_data__field_indices_by_name[] = {
  3,   /* field[3] = AcceptedID */
  4,   /* field[4] = AcceptedNodeID */
  5,   /* field[5] = AcceptedValue */
  6,   /* field[6] = Checksum */
  0,   /* field[0] = InstanceID */
  1,   /* field[1] = PromiseID */
  2,   /* field[2] = PromiseNodeID */
};
static const ProtobufCIntRange xh__acceptor_state_data__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 7 }
};
const ProtobufCMessageDescriptor xh__acceptor_state_data__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "xh.AcceptorStateData",
  "AcceptorStateData",
  "Xh__AcceptorStateData",
  "xh",
  sizeof(Xh__AcceptorStateData),
  7,
  xh__acceptor_state_data__field_descriptors,
  xh__acceptor_state_data__field_indices_by_name,
  1,  xh__acceptor_state_data__number_ranges,
  (ProtobufCMessageInit) xh__acceptor_state_data__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor xh__paxos_node_info__field_descriptors[2] =
{
  {
    "Rid",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__PaxosNodeInfo, rid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Nodeid",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__PaxosNodeInfo, nodeid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned xh__paxos_node_info__field_indices_by_name[] = {
  1,   /* field[1] = Nodeid */
  0,   /* field[0] = Rid */
};
static const ProtobufCIntRange xh__paxos_node_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor xh__paxos_node_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "xh.PaxosNodeInfo",
  "PaxosNodeInfo",
  "Xh__PaxosNodeInfo",
  "xh",
  sizeof(Xh__PaxosNodeInfo),
  2,
  xh__paxos_node_info__field_descriptors,
  xh__paxos_node_info__field_indices_by_name,
  1,  xh__paxos_node_info__number_ranges,
  (ProtobufCMessageInit) xh__paxos_node_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor xh__system_variables__field_descriptors[3] =
{
  {
    "Gid",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__SystemVariables, gid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "MemberShip",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Xh__SystemVariables, n_membership),
    offsetof(Xh__SystemVariables, membership),
    &xh__paxos_node_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Version",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__SystemVariables, version),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned xh__system_variables__field_indices_by_name[] = {
  0,   /* field[0] = Gid */
  1,   /* field[1] = MemberShip */
  2,   /* field[2] = Version */
};
static const ProtobufCIntRange xh__system_variables__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor xh__system_variables__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "xh.SystemVariables",
  "SystemVariables",
  "Xh__SystemVariables",
  "xh",
  sizeof(Xh__SystemVariables),
  3,
  xh__system_variables__field_descriptors,
  xh__system_variables__field_indices_by_name,
  1,  xh__system_variables__number_ranges,
  (ProtobufCMessageInit) xh__system_variables__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor xh__master_variables__field_descriptors[3] =
{
  {
    "MasterNodeid",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__MasterVariables, masternodeid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Version",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(Xh__MasterVariables, version),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "LeaseTime",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Xh__MasterVariables, leasetime),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned xh__master_variables__field_indices_by_name[] = {
  2,   /* field[2] = LeaseTime */
  0,   /* field[0] = MasterNodeid */
  1,   /* field[1] = Version */
};
static const ProtobufCIntRange xh__master_variables__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor xh__master_variables__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "xh.MasterVariables",
  "MasterVariables",
  "Xh__MasterVariables",
  "xh",
  sizeof(Xh__MasterVariables),
  3,
  xh__master_variables__field_descriptors,
  xh__master_variables__field_indices_by_name,
  1,  xh__master_variables__number_ranges,
  (ProtobufCMessageInit) xh__master_variables__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor xh__paxos_value__field_descriptors[2] =
{
  {
    "SMID",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Xh__PaxosValue, smid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Value",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(Xh__PaxosValue, value),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned xh__paxos_value__field_indices_by_name[] = {
  0,   /* field[0] = SMID */
  1,   /* field[1] = Value */
};
static const ProtobufCIntRange xh__paxos_value__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor xh__paxos_value__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "xh.PaxosValue",
  "PaxosValue",
  "Xh__PaxosValue",
  "xh",
  sizeof(Xh__PaxosValue),
  2,
  xh__paxos_value__field_descriptors,
  xh__paxos_value__field_indices_by_name,
  1,  xh__paxos_value__number_ranges,
  (ProtobufCMessageInit) xh__paxos_value__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor xh__batch_paxos_values__field_descriptors[1] =
{
  {
    "Values",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Xh__BatchPaxosValues, n_values),
    offsetof(Xh__BatchPaxosValues, values),
    &xh__paxos_value__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned xh__batch_paxos_values__field_indices_by_name[] = {
  0,   /* field[0] = Values */
};
static const ProtobufCIntRange xh__batch_paxos_values__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor xh__batch_paxos_values__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "xh.BatchPaxosValues",
  "BatchPaxosValues",
  "Xh__BatchPaxosValues",
  "xh",
  sizeof(Xh__BatchPaxosValues),
  1,
  xh__batch_paxos_values__field_descriptors,
  xh__batch_paxos_values__field_indices_by_name,
  1,  xh__batch_paxos_values__number_ranges,
  (ProtobufCMessageInit) xh__batch_paxos_values__init,
  NULL,NULL,NULL    /* reserved[123] */
};