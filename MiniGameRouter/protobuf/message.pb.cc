// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#include "message.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR EndpointProto::EndpointProto(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.ip_address_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.svc_name_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.port_)*/0
  , /*decltype(_impl_.weight_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct EndpointProtoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR EndpointProtoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~EndpointProtoDefaultTypeInternal() {}
  union {
    EndpointProto _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 EndpointProtoDefaultTypeInternal _EndpointProto_default_instance_;
PROTOBUF_CONSTEXPR MessageProto::MessageProto(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.key_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.content_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.timestamp_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.sender_)*/nullptr
  , /*decltype(_impl_.receiver_)*/nullptr
  , /*decltype(_impl_.m_type_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct MessageProtoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR MessageProtoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~MessageProtoDefaultTypeInternal() {}
  union {
    MessageProto _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 MessageProtoDefaultTypeInternal _MessageProto_default_instance_;
PROTOBUF_CONSTEXPR ContentProto::ContentProto(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.eps_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct ContentProtoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ContentProtoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ContentProtoDefaultTypeInternal() {}
  union {
    ContentProto _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ContentProtoDefaultTypeInternal _ContentProto_default_instance_;
static ::_pb::Metadata file_level_metadata_message_2eproto[3];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_message_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_message_2eproto = nullptr;

const uint32_t TableStruct_message_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::EndpointProto, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::EndpointProto, _impl_.ip_address_),
  PROTOBUF_FIELD_OFFSET(::EndpointProto, _impl_.port_),
  PROTOBUF_FIELD_OFFSET(::EndpointProto, _impl_.svc_name_),
  PROTOBUF_FIELD_OFFSET(::EndpointProto, _impl_.weight_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::MessageProto, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::MessageProto, _impl_.sender_),
  PROTOBUF_FIELD_OFFSET(::MessageProto, _impl_.receiver_),
  PROTOBUF_FIELD_OFFSET(::MessageProto, _impl_.key_),
  PROTOBUF_FIELD_OFFSET(::MessageProto, _impl_.m_type_),
  PROTOBUF_FIELD_OFFSET(::MessageProto, _impl_.content_),
  PROTOBUF_FIELD_OFFSET(::MessageProto, _impl_.timestamp_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ContentProto, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ContentProto, _impl_.eps_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::EndpointProto)},
  { 10, -1, -1, sizeof(::MessageProto)},
  { 22, -1, -1, sizeof(::ContentProto)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_EndpointProto_default_instance_._instance,
  &::_MessageProto_default_instance_._instance,
  &::_ContentProto_default_instance_._instance,
};

const char descriptor_table_protodef_message_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rmessage.proto\"S\n\rEndpointProto\022\022\n\nip_a"
  "ddress\030\001 \001(\t\022\014\n\004port\030\002 \001(\005\022\020\n\010svc_name\030\003"
  " \001(\t\022\016\n\006weight\030\004 \001(\005\"\221\001\n\014MessageProto\022\036\n"
  "\006sender\030\001 \001(\0132\016.EndpointProto\022 \n\010receive"
  "r\030\002 \001(\0132\016.EndpointProto\022\013\n\003key\030\003 \001(\t\022\016\n\006"
  "m_type\030\004 \001(\005\022\017\n\007content\030\005 \001(\t\022\021\n\ttimesta"
  "mp\030\006 \001(\t\"+\n\014ContentProto\022\033\n\003eps\030\001 \003(\0132\016."
  "EndpointProtob\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_message_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_message_2eproto = {
    false, false, 301, descriptor_table_protodef_message_2eproto,
    "message.proto",
    &descriptor_table_message_2eproto_once, nullptr, 0, 3,
    schemas, file_default_instances, TableStruct_message_2eproto::offsets,
    file_level_metadata_message_2eproto, file_level_enum_descriptors_message_2eproto,
    file_level_service_descriptors_message_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_message_2eproto_getter() {
  return &descriptor_table_message_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_message_2eproto(&descriptor_table_message_2eproto);

// ===================================================================

class EndpointProto::_Internal {
 public:
};

EndpointProto::EndpointProto(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:EndpointProto)
}
EndpointProto::EndpointProto(const EndpointProto& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  EndpointProto* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.ip_address_){}
    , decltype(_impl_.svc_name_){}
    , decltype(_impl_.port_){}
    , decltype(_impl_.weight_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.ip_address_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.ip_address_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_ip_address().empty()) {
    _this->_impl_.ip_address_.Set(from._internal_ip_address(), 
      _this->GetArenaForAllocation());
  }
  _impl_.svc_name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.svc_name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_svc_name().empty()) {
    _this->_impl_.svc_name_.Set(from._internal_svc_name(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.port_, &from._impl_.port_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.weight_) -
    reinterpret_cast<char*>(&_impl_.port_)) + sizeof(_impl_.weight_));
  // @@protoc_insertion_point(copy_constructor:EndpointProto)
}

inline void EndpointProto::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.ip_address_){}
    , decltype(_impl_.svc_name_){}
    , decltype(_impl_.port_){0}
    , decltype(_impl_.weight_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.ip_address_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.ip_address_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.svc_name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.svc_name_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

EndpointProto::~EndpointProto() {
  // @@protoc_insertion_point(destructor:EndpointProto)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void EndpointProto::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.ip_address_.Destroy();
  _impl_.svc_name_.Destroy();
}

void EndpointProto::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void EndpointProto::Clear() {
// @@protoc_insertion_point(message_clear_start:EndpointProto)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.ip_address_.ClearToEmpty();
  _impl_.svc_name_.ClearToEmpty();
  ::memset(&_impl_.port_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.weight_) -
      reinterpret_cast<char*>(&_impl_.port_)) + sizeof(_impl_.weight_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* EndpointProto::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string ip_address = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_ip_address();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "EndpointProto.ip_address"));
        } else
          goto handle_unusual;
        continue;
      // int32 port = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.port_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string svc_name = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_svc_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "EndpointProto.svc_name"));
        } else
          goto handle_unusual;
        continue;
      // int32 weight = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.weight_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* EndpointProto::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:EndpointProto)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string ip_address = 1;
  if (!this->_internal_ip_address().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_ip_address().data(), static_cast<int>(this->_internal_ip_address().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "EndpointProto.ip_address");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_ip_address(), target);
  }

  // int32 port = 2;
  if (this->_internal_port() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_port(), target);
  }

  // string svc_name = 3;
  if (!this->_internal_svc_name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_svc_name().data(), static_cast<int>(this->_internal_svc_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "EndpointProto.svc_name");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_svc_name(), target);
  }

  // int32 weight = 4;
  if (this->_internal_weight() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_weight(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:EndpointProto)
  return target;
}

size_t EndpointProto::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:EndpointProto)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string ip_address = 1;
  if (!this->_internal_ip_address().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_ip_address());
  }

  // string svc_name = 3;
  if (!this->_internal_svc_name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_svc_name());
  }

  // int32 port = 2;
  if (this->_internal_port() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_port());
  }

  // int32 weight = 4;
  if (this->_internal_weight() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_weight());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData EndpointProto::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    EndpointProto::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*EndpointProto::GetClassData() const { return &_class_data_; }


void EndpointProto::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<EndpointProto*>(&to_msg);
  auto& from = static_cast<const EndpointProto&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:EndpointProto)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_ip_address().empty()) {
    _this->_internal_set_ip_address(from._internal_ip_address());
  }
  if (!from._internal_svc_name().empty()) {
    _this->_internal_set_svc_name(from._internal_svc_name());
  }
  if (from._internal_port() != 0) {
    _this->_internal_set_port(from._internal_port());
  }
  if (from._internal_weight() != 0) {
    _this->_internal_set_weight(from._internal_weight());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void EndpointProto::CopyFrom(const EndpointProto& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:EndpointProto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EndpointProto::IsInitialized() const {
  return true;
}

void EndpointProto::InternalSwap(EndpointProto* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.ip_address_, lhs_arena,
      &other->_impl_.ip_address_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.svc_name_, lhs_arena,
      &other->_impl_.svc_name_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(EndpointProto, _impl_.weight_)
      + sizeof(EndpointProto::_impl_.weight_)
      - PROTOBUF_FIELD_OFFSET(EndpointProto, _impl_.port_)>(
          reinterpret_cast<char*>(&_impl_.port_),
          reinterpret_cast<char*>(&other->_impl_.port_));
}

::PROTOBUF_NAMESPACE_ID::Metadata EndpointProto::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_message_2eproto_getter, &descriptor_table_message_2eproto_once,
      file_level_metadata_message_2eproto[0]);
}

// ===================================================================

class MessageProto::_Internal {
 public:
  static const ::EndpointProto& sender(const MessageProto* msg);
  static const ::EndpointProto& receiver(const MessageProto* msg);
};

const ::EndpointProto&
MessageProto::_Internal::sender(const MessageProto* msg) {
  return *msg->_impl_.sender_;
}
const ::EndpointProto&
MessageProto::_Internal::receiver(const MessageProto* msg) {
  return *msg->_impl_.receiver_;
}
MessageProto::MessageProto(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:MessageProto)
}
MessageProto::MessageProto(const MessageProto& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  MessageProto* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.key_){}
    , decltype(_impl_.content_){}
    , decltype(_impl_.timestamp_){}
    , decltype(_impl_.sender_){nullptr}
    , decltype(_impl_.receiver_){nullptr}
    , decltype(_impl_.m_type_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.key_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.key_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_key().empty()) {
    _this->_impl_.key_.Set(from._internal_key(), 
      _this->GetArenaForAllocation());
  }
  _impl_.content_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.content_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_content().empty()) {
    _this->_impl_.content_.Set(from._internal_content(), 
      _this->GetArenaForAllocation());
  }
  _impl_.timestamp_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.timestamp_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_timestamp().empty()) {
    _this->_impl_.timestamp_.Set(from._internal_timestamp(), 
      _this->GetArenaForAllocation());
  }
  if (from._internal_has_sender()) {
    _this->_impl_.sender_ = new ::EndpointProto(*from._impl_.sender_);
  }
  if (from._internal_has_receiver()) {
    _this->_impl_.receiver_ = new ::EndpointProto(*from._impl_.receiver_);
  }
  _this->_impl_.m_type_ = from._impl_.m_type_;
  // @@protoc_insertion_point(copy_constructor:MessageProto)
}

inline void MessageProto::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.key_){}
    , decltype(_impl_.content_){}
    , decltype(_impl_.timestamp_){}
    , decltype(_impl_.sender_){nullptr}
    , decltype(_impl_.receiver_){nullptr}
    , decltype(_impl_.m_type_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.key_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.key_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.content_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.content_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.timestamp_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.timestamp_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

MessageProto::~MessageProto() {
  // @@protoc_insertion_point(destructor:MessageProto)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void MessageProto::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.key_.Destroy();
  _impl_.content_.Destroy();
  _impl_.timestamp_.Destroy();
  if (this != internal_default_instance()) delete _impl_.sender_;
  if (this != internal_default_instance()) delete _impl_.receiver_;
}

void MessageProto::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void MessageProto::Clear() {
// @@protoc_insertion_point(message_clear_start:MessageProto)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.key_.ClearToEmpty();
  _impl_.content_.ClearToEmpty();
  _impl_.timestamp_.ClearToEmpty();
  if (GetArenaForAllocation() == nullptr && _impl_.sender_ != nullptr) {
    delete _impl_.sender_;
  }
  _impl_.sender_ = nullptr;
  if (GetArenaForAllocation() == nullptr && _impl_.receiver_ != nullptr) {
    delete _impl_.receiver_;
  }
  _impl_.receiver_ = nullptr;
  _impl_.m_type_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MessageProto::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .EndpointProto sender = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_sender(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .EndpointProto receiver = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_receiver(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string key = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_key();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "MessageProto.key"));
        } else
          goto handle_unusual;
        continue;
      // int32 m_type = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.m_type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string content = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          auto str = _internal_mutable_content();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "MessageProto.content"));
        } else
          goto handle_unusual;
        continue;
      // string timestamp = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 50)) {
          auto str = _internal_mutable_timestamp();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "MessageProto.timestamp"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* MessageProto::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:MessageProto)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .EndpointProto sender = 1;
  if (this->_internal_has_sender()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::sender(this),
        _Internal::sender(this).GetCachedSize(), target, stream);
  }

  // .EndpointProto receiver = 2;
  if (this->_internal_has_receiver()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(2, _Internal::receiver(this),
        _Internal::receiver(this).GetCachedSize(), target, stream);
  }

  // string key = 3;
  if (!this->_internal_key().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_key().data(), static_cast<int>(this->_internal_key().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MessageProto.key");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_key(), target);
  }

  // int32 m_type = 4;
  if (this->_internal_m_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_m_type(), target);
  }

  // string content = 5;
  if (!this->_internal_content().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_content().data(), static_cast<int>(this->_internal_content().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MessageProto.content");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_content(), target);
  }

  // string timestamp = 6;
  if (!this->_internal_timestamp().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_timestamp().data(), static_cast<int>(this->_internal_timestamp().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MessageProto.timestamp");
    target = stream->WriteStringMaybeAliased(
        6, this->_internal_timestamp(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MessageProto)
  return target;
}

size_t MessageProto::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MessageProto)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string key = 3;
  if (!this->_internal_key().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_key());
  }

  // string content = 5;
  if (!this->_internal_content().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_content());
  }

  // string timestamp = 6;
  if (!this->_internal_timestamp().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_timestamp());
  }

  // .EndpointProto sender = 1;
  if (this->_internal_has_sender()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.sender_);
  }

  // .EndpointProto receiver = 2;
  if (this->_internal_has_receiver()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.receiver_);
  }

  // int32 m_type = 4;
  if (this->_internal_m_type() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_m_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MessageProto::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    MessageProto::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MessageProto::GetClassData() const { return &_class_data_; }


void MessageProto::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<MessageProto*>(&to_msg);
  auto& from = static_cast<const MessageProto&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:MessageProto)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_key().empty()) {
    _this->_internal_set_key(from._internal_key());
  }
  if (!from._internal_content().empty()) {
    _this->_internal_set_content(from._internal_content());
  }
  if (!from._internal_timestamp().empty()) {
    _this->_internal_set_timestamp(from._internal_timestamp());
  }
  if (from._internal_has_sender()) {
    _this->_internal_mutable_sender()->::EndpointProto::MergeFrom(
        from._internal_sender());
  }
  if (from._internal_has_receiver()) {
    _this->_internal_mutable_receiver()->::EndpointProto::MergeFrom(
        from._internal_receiver());
  }
  if (from._internal_m_type() != 0) {
    _this->_internal_set_m_type(from._internal_m_type());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MessageProto::CopyFrom(const MessageProto& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MessageProto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageProto::IsInitialized() const {
  return true;
}

void MessageProto::InternalSwap(MessageProto* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.key_, lhs_arena,
      &other->_impl_.key_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.content_, lhs_arena,
      &other->_impl_.content_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.timestamp_, lhs_arena,
      &other->_impl_.timestamp_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(MessageProto, _impl_.m_type_)
      + sizeof(MessageProto::_impl_.m_type_)
      - PROTOBUF_FIELD_OFFSET(MessageProto, _impl_.sender_)>(
          reinterpret_cast<char*>(&_impl_.sender_),
          reinterpret_cast<char*>(&other->_impl_.sender_));
}

::PROTOBUF_NAMESPACE_ID::Metadata MessageProto::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_message_2eproto_getter, &descriptor_table_message_2eproto_once,
      file_level_metadata_message_2eproto[1]);
}

// ===================================================================

class ContentProto::_Internal {
 public:
};

ContentProto::ContentProto(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:ContentProto)
}
ContentProto::ContentProto(const ContentProto& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  ContentProto* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.eps_){from._impl_.eps_}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:ContentProto)
}

inline void ContentProto::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.eps_){arena}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

ContentProto::~ContentProto() {
  // @@protoc_insertion_point(destructor:ContentProto)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void ContentProto::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.eps_.~RepeatedPtrField();
}

void ContentProto::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void ContentProto::Clear() {
// @@protoc_insertion_point(message_clear_start:ContentProto)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.eps_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ContentProto::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .EndpointProto eps = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_eps(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* ContentProto::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ContentProto)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .EndpointProto eps = 1;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_eps_size()); i < n; i++) {
    const auto& repfield = this->_internal_eps(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(1, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ContentProto)
  return target;
}

size_t ContentProto::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ContentProto)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .EndpointProto eps = 1;
  total_size += 1UL * this->_internal_eps_size();
  for (const auto& msg : this->_impl_.eps_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ContentProto::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    ContentProto::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ContentProto::GetClassData() const { return &_class_data_; }


void ContentProto::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<ContentProto*>(&to_msg);
  auto& from = static_cast<const ContentProto&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ContentProto)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.eps_.MergeFrom(from._impl_.eps_);
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ContentProto::CopyFrom(const ContentProto& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ContentProto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ContentProto::IsInitialized() const {
  return true;
}

void ContentProto::InternalSwap(ContentProto* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.eps_.InternalSwap(&other->_impl_.eps_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ContentProto::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_message_2eproto_getter, &descriptor_table_message_2eproto_once,
      file_level_metadata_message_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::EndpointProto*
Arena::CreateMaybeMessage< ::EndpointProto >(Arena* arena) {
  return Arena::CreateMessageInternal< ::EndpointProto >(arena);
}
template<> PROTOBUF_NOINLINE ::MessageProto*
Arena::CreateMaybeMessage< ::MessageProto >(Arena* arena) {
  return Arena::CreateMessageInternal< ::MessageProto >(arena);
}
template<> PROTOBUF_NOINLINE ::ContentProto*
Arena::CreateMaybeMessage< ::ContentProto >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ContentProto >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
