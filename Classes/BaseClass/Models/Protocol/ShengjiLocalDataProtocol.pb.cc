// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ShengjiLocalDataProtocol.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ShengjiLocalDataProtocol.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* AccountInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AccountInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* AccountVector_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AccountVector_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_ShengjiLocalDataProtocol_2eproto() {
  protobuf_AddDesc_ShengjiLocalDataProtocol_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ShengjiLocalDataProtocol.proto");
  GOOGLE_CHECK(file != NULL);
  AccountInfo_descriptor_ = file->message_type(0);
  static const int AccountInfo_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, account_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, account_password_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, nick_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, face_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, user_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, vip_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, vip_level_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, vip_year_status_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, head_frame_type_),
  };
  AccountInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AccountInfo_descriptor_,
      AccountInfo::default_instance_,
      AccountInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AccountInfo));
  AccountVector_descriptor_ = file->message_type(1);
  static const int AccountVector_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountVector, account_vector_),
  };
  AccountVector_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AccountVector_descriptor_,
      AccountVector::default_instance_,
      AccountVector_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountVector, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AccountVector, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AccountVector));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ShengjiLocalDataProtocol_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AccountInfo_descriptor_, &AccountInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AccountVector_descriptor_, &AccountVector::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_ShengjiLocalDataProtocol_2eproto() {
  delete AccountInfo::default_instance_;
  delete AccountInfo_reflection_;
  delete AccountVector::default_instance_;
  delete AccountVector_reflection_;
}

void protobuf_AddDesc_ShengjiLocalDataProtocol_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\036ShengjiLocalDataProtocol.proto\"\311\001\n\013Acc"
    "ountInfo\022\024\n\014account_name\030\001 \002(\t\022\030\n\020accoun"
    "t_password\030\002 \002(\t\022\021\n\tnick_name\030\003 \002(\t\022\017\n\007f"
    "ace_id\030\004 \002(\r\022\017\n\007user_id\030\005 \002(\004\022\020\n\010vip_typ"
    "e\030\006 \002(\r\022\021\n\tvip_level\030\007 \002(\r\022\027\n\017vip_year_s"
    "tatus\030\010 \002(\r\022\027\n\017head_frame_type\030\t \002(\r\"5\n\r"
    "AccountVector\022$\n\016account_vector\030\001 \003(\0132\014."
    "AccountInfo", 291);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ShengjiLocalDataProtocol.proto", &protobuf_RegisterTypes);
  AccountInfo::default_instance_ = new AccountInfo();
  AccountVector::default_instance_ = new AccountVector();
  AccountInfo::default_instance_->InitAsDefaultInstance();
  AccountVector::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ShengjiLocalDataProtocol_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ShengjiLocalDataProtocol_2eproto {
  StaticDescriptorInitializer_ShengjiLocalDataProtocol_2eproto() {
    protobuf_AddDesc_ShengjiLocalDataProtocol_2eproto();
  }
} static_descriptor_initializer_ShengjiLocalDataProtocol_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int AccountInfo::kAccountNameFieldNumber;
const int AccountInfo::kAccountPasswordFieldNumber;
const int AccountInfo::kNickNameFieldNumber;
const int AccountInfo::kFaceIdFieldNumber;
const int AccountInfo::kUserIdFieldNumber;
const int AccountInfo::kVipTypeFieldNumber;
const int AccountInfo::kVipLevelFieldNumber;
const int AccountInfo::kVipYearStatusFieldNumber;
const int AccountInfo::kHeadFrameTypeFieldNumber;
#endif  // !_MSC_VER

AccountInfo::AccountInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AccountInfo::InitAsDefaultInstance() {
}

AccountInfo::AccountInfo(const AccountInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AccountInfo::SharedCtor() {
  _cached_size_ = 0;
  account_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  account_password_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  nick_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  face_id_ = 0u;
  user_id_ = GOOGLE_ULONGLONG(0);
  vip_type_ = 0u;
  vip_level_ = 0u;
  vip_year_status_ = 0u;
  head_frame_type_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AccountInfo::~AccountInfo() {
  SharedDtor();
}

void AccountInfo::SharedDtor() {
  if (account_name_ != &::google::protobuf::internal::kEmptyString) {
    delete account_name_;
  }
  if (account_password_ != &::google::protobuf::internal::kEmptyString) {
    delete account_password_;
  }
  if (nick_name_ != &::google::protobuf::internal::kEmptyString) {
    delete nick_name_;
  }
  if (this != default_instance_) {
  }
}

void AccountInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AccountInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AccountInfo_descriptor_;
}

const AccountInfo& AccountInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ShengjiLocalDataProtocol_2eproto();
  return *default_instance_;
}

AccountInfo* AccountInfo::default_instance_ = NULL;

AccountInfo* AccountInfo::New() const {
  return new AccountInfo;
}

void AccountInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_account_name()) {
      if (account_name_ != &::google::protobuf::internal::kEmptyString) {
        account_name_->clear();
      }
    }
    if (has_account_password()) {
      if (account_password_ != &::google::protobuf::internal::kEmptyString) {
        account_password_->clear();
      }
    }
    if (has_nick_name()) {
      if (nick_name_ != &::google::protobuf::internal::kEmptyString) {
        nick_name_->clear();
      }
    }
    face_id_ = 0u;
    user_id_ = GOOGLE_ULONGLONG(0);
    vip_type_ = 0u;
    vip_level_ = 0u;
    vip_year_status_ = 0u;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    head_frame_type_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AccountInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string account_name = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_account_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->account_name().data(), this->account_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_account_password;
        break;
      }

      // required string account_password = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_account_password:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_account_password()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->account_password().data(), this->account_password().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_nick_name;
        break;
      }

      // required string nick_name = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_nick_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_nick_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->nick_name().data(), this->nick_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_face_id;
        break;
      }

      // required uint32 face_id = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_face_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &face_id_)));
          set_has_face_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_user_id;
        break;
      }

      // required uint64 user_id = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_user_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &user_id_)));
          set_has_user_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(48)) goto parse_vip_type;
        break;
      }

      // required uint32 vip_type = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_vip_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &vip_type_)));
          set_has_vip_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(56)) goto parse_vip_level;
        break;
      }

      // required uint32 vip_level = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_vip_level:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &vip_level_)));
          set_has_vip_level();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_vip_year_status;
        break;
      }

      // required uint32 vip_year_status = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_vip_year_status:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &vip_year_status_)));
          set_has_vip_year_status();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(72)) goto parse_head_frame_type;
        break;
      }

      // required uint32 head_frame_type = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_head_frame_type:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &head_frame_type_)));
          set_has_head_frame_type();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void AccountInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string account_name = 1;
  if (has_account_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->account_name().data(), this->account_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->account_name(), output);
  }

  // required string account_password = 2;
  if (has_account_password()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->account_password().data(), this->account_password().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->account_password(), output);
  }

  // required string nick_name = 3;
  if (has_nick_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->nick_name().data(), this->nick_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->nick_name(), output);
  }

  // required uint32 face_id = 4;
  if (has_face_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->face_id(), output);
  }

  // required uint64 user_id = 5;
  if (has_user_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(5, this->user_id(), output);
  }

  // required uint32 vip_type = 6;
  if (has_vip_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->vip_type(), output);
  }

  // required uint32 vip_level = 7;
  if (has_vip_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->vip_level(), output);
  }

  // required uint32 vip_year_status = 8;
  if (has_vip_year_status()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->vip_year_status(), output);
  }

  // required uint32 head_frame_type = 9;
  if (has_head_frame_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->head_frame_type(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AccountInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string account_name = 1;
  if (has_account_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->account_name().data(), this->account_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->account_name(), target);
  }

  // required string account_password = 2;
  if (has_account_password()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->account_password().data(), this->account_password().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->account_password(), target);
  }

  // required string nick_name = 3;
  if (has_nick_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->nick_name().data(), this->nick_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->nick_name(), target);
  }

  // required uint32 face_id = 4;
  if (has_face_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->face_id(), target);
  }

  // required uint64 user_id = 5;
  if (has_user_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(5, this->user_id(), target);
  }

  // required uint32 vip_type = 6;
  if (has_vip_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(6, this->vip_type(), target);
  }

  // required uint32 vip_level = 7;
  if (has_vip_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(7, this->vip_level(), target);
  }

  // required uint32 vip_year_status = 8;
  if (has_vip_year_status()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(8, this->vip_year_status(), target);
  }

  // required uint32 head_frame_type = 9;
  if (has_head_frame_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(9, this->head_frame_type(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AccountInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string account_name = 1;
    if (has_account_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->account_name());
    }

    // required string account_password = 2;
    if (has_account_password()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->account_password());
    }

    // required string nick_name = 3;
    if (has_nick_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->nick_name());
    }

    // required uint32 face_id = 4;
    if (has_face_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->face_id());
    }

    // required uint64 user_id = 5;
    if (has_user_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->user_id());
    }

    // required uint32 vip_type = 6;
    if (has_vip_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->vip_type());
    }

    // required uint32 vip_level = 7;
    if (has_vip_level()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->vip_level());
    }

    // required uint32 vip_year_status = 8;
    if (has_vip_year_status()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->vip_year_status());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // required uint32 head_frame_type = 9;
    if (has_head_frame_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->head_frame_type());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void AccountInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AccountInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AccountInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AccountInfo::MergeFrom(const AccountInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_account_name()) {
      set_account_name(from.account_name());
    }
    if (from.has_account_password()) {
      set_account_password(from.account_password());
    }
    if (from.has_nick_name()) {
      set_nick_name(from.nick_name());
    }
    if (from.has_face_id()) {
      set_face_id(from.face_id());
    }
    if (from.has_user_id()) {
      set_user_id(from.user_id());
    }
    if (from.has_vip_type()) {
      set_vip_type(from.vip_type());
    }
    if (from.has_vip_level()) {
      set_vip_level(from.vip_level());
    }
    if (from.has_vip_year_status()) {
      set_vip_year_status(from.vip_year_status());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_head_frame_type()) {
      set_head_frame_type(from.head_frame_type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AccountInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AccountInfo::CopyFrom(const AccountInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AccountInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x000001ff) != 0x000001ff) return false;

  return true;
}

void AccountInfo::Swap(AccountInfo* other) {
  if (other != this) {
    std::swap(account_name_, other->account_name_);
    std::swap(account_password_, other->account_password_);
    std::swap(nick_name_, other->nick_name_);
    std::swap(face_id_, other->face_id_);
    std::swap(user_id_, other->user_id_);
    std::swap(vip_type_, other->vip_type_);
    std::swap(vip_level_, other->vip_level_);
    std::swap(vip_year_status_, other->vip_year_status_);
    std::swap(head_frame_type_, other->head_frame_type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AccountInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AccountInfo_descriptor_;
  metadata.reflection = AccountInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AccountVector::kAccountVectorFieldNumber;
#endif  // !_MSC_VER

AccountVector::AccountVector()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void AccountVector::InitAsDefaultInstance() {
}

AccountVector::AccountVector(const AccountVector& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void AccountVector::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AccountVector::~AccountVector() {
  SharedDtor();
}

void AccountVector::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AccountVector::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AccountVector::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AccountVector_descriptor_;
}

const AccountVector& AccountVector::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_ShengjiLocalDataProtocol_2eproto();
  return *default_instance_;
}

AccountVector* AccountVector::default_instance_ = NULL;

AccountVector* AccountVector::New() const {
  return new AccountVector;
}

void AccountVector::Clear() {
  account_vector_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AccountVector::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .AccountInfo account_vector = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_account_vector:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_account_vector()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_account_vector;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void AccountVector::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .AccountInfo account_vector = 1;
  for (int i = 0; i < this->account_vector_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->account_vector(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* AccountVector::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .AccountInfo account_vector = 1;
  for (int i = 0; i < this->account_vector_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->account_vector(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int AccountVector::ByteSize() const {
  int total_size = 0;

  // repeated .AccountInfo account_vector = 1;
  total_size += 1 * this->account_vector_size();
  for (int i = 0; i < this->account_vector_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->account_vector(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void AccountVector::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AccountVector* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AccountVector*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AccountVector::MergeFrom(const AccountVector& from) {
  GOOGLE_CHECK_NE(&from, this);
  account_vector_.MergeFrom(from.account_vector_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AccountVector::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AccountVector::CopyFrom(const AccountVector& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AccountVector::IsInitialized() const {

  for (int i = 0; i < account_vector_size(); i++) {
    if (!this->account_vector(i).IsInitialized()) return false;
  }
  return true;
}

void AccountVector::Swap(AccountVector* other) {
  if (other != this) {
    account_vector_.Swap(&other->account_vector_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AccountVector::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AccountVector_descriptor_;
  metadata.reflection = AccountVector_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
