// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ShengjiLocalDataProtocol.proto

#ifndef PROTOBUF_ShengjiLocalDataProtocol_2eproto__INCLUDED
#define PROTOBUF_ShengjiLocalDataProtocol_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ShengjiLocalDataProtocol_2eproto();
void protobuf_AssignDesc_ShengjiLocalDataProtocol_2eproto();
void protobuf_ShutdownFile_ShengjiLocalDataProtocol_2eproto();

class AccountInfo;
class AccountVector;

// ===================================================================

class AccountInfo : public ::google::protobuf::Message {
 public:
  AccountInfo();
  virtual ~AccountInfo();

  AccountInfo(const AccountInfo& from);

  inline AccountInfo& operator=(const AccountInfo& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AccountInfo& default_instance();

  void Swap(AccountInfo* other);

  // implements Message ----------------------------------------------

  AccountInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AccountInfo& from);
  void MergeFrom(const AccountInfo& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string account_name = 1;
  inline bool has_account_name() const;
  inline void clear_account_name();
  static const int kAccountNameFieldNumber = 1;
  inline const ::std::string& account_name() const;
  inline void set_account_name(const ::std::string& value);
  inline void set_account_name(const char* value);
  inline void set_account_name(const char* value, size_t size);
  inline ::std::string* mutable_account_name();
  inline ::std::string* release_account_name();
  inline void set_allocated_account_name(::std::string* account_name);

  // required string account_password = 2;
  inline bool has_account_password() const;
  inline void clear_account_password();
  static const int kAccountPasswordFieldNumber = 2;
  inline const ::std::string& account_password() const;
  inline void set_account_password(const ::std::string& value);
  inline void set_account_password(const char* value);
  inline void set_account_password(const char* value, size_t size);
  inline ::std::string* mutable_account_password();
  inline ::std::string* release_account_password();
  inline void set_allocated_account_password(::std::string* account_password);

  // required string nick_name = 3;
  inline bool has_nick_name() const;
  inline void clear_nick_name();
  static const int kNickNameFieldNumber = 3;
  inline const ::std::string& nick_name() const;
  inline void set_nick_name(const ::std::string& value);
  inline void set_nick_name(const char* value);
  inline void set_nick_name(const char* value, size_t size);
  inline ::std::string* mutable_nick_name();
  inline ::std::string* release_nick_name();
  inline void set_allocated_nick_name(::std::string* nick_name);

  // required uint32 face_id = 4;
  inline bool has_face_id() const;
  inline void clear_face_id();
  static const int kFaceIdFieldNumber = 4;
  inline ::google::protobuf::uint32 face_id() const;
  inline void set_face_id(::google::protobuf::uint32 value);

  // required uint64 user_id = 5;
  inline bool has_user_id() const;
  inline void clear_user_id();
  static const int kUserIdFieldNumber = 5;
  inline ::google::protobuf::uint64 user_id() const;
  inline void set_user_id(::google::protobuf::uint64 value);

  // required uint32 vip_type = 6;
  inline bool has_vip_type() const;
  inline void clear_vip_type();
  static const int kVipTypeFieldNumber = 6;
  inline ::google::protobuf::uint32 vip_type() const;
  inline void set_vip_type(::google::protobuf::uint32 value);

  // required uint32 vip_level = 7;
  inline bool has_vip_level() const;
  inline void clear_vip_level();
  static const int kVipLevelFieldNumber = 7;
  inline ::google::protobuf::uint32 vip_level() const;
  inline void set_vip_level(::google::protobuf::uint32 value);

  // required uint32 vip_year_status = 8;
  inline bool has_vip_year_status() const;
  inline void clear_vip_year_status();
  static const int kVipYearStatusFieldNumber = 8;
  inline ::google::protobuf::uint32 vip_year_status() const;
  inline void set_vip_year_status(::google::protobuf::uint32 value);

  // required uint32 head_frame_type = 9;
  inline bool has_head_frame_type() const;
  inline void clear_head_frame_type();
  static const int kHeadFrameTypeFieldNumber = 9;
  inline ::google::protobuf::uint32 head_frame_type() const;
  inline void set_head_frame_type(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:AccountInfo)
 private:
  inline void set_has_account_name();
  inline void clear_has_account_name();
  inline void set_has_account_password();
  inline void clear_has_account_password();
  inline void set_has_nick_name();
  inline void clear_has_nick_name();
  inline void set_has_face_id();
  inline void clear_has_face_id();
  inline void set_has_user_id();
  inline void clear_has_user_id();
  inline void set_has_vip_type();
  inline void clear_has_vip_type();
  inline void set_has_vip_level();
  inline void clear_has_vip_level();
  inline void set_has_vip_year_status();
  inline void clear_has_vip_year_status();
  inline void set_has_head_frame_type();
  inline void clear_has_head_frame_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* account_name_;
  ::std::string* account_password_;
  ::std::string* nick_name_;
  ::google::protobuf::uint64 user_id_;
  ::google::protobuf::uint32 face_id_;
  ::google::protobuf::uint32 vip_type_;
  ::google::protobuf::uint32 vip_level_;
  ::google::protobuf::uint32 vip_year_status_;
  ::google::protobuf::uint32 head_frame_type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(9 + 31) / 32];

  friend void  protobuf_AddDesc_ShengjiLocalDataProtocol_2eproto();
  friend void protobuf_AssignDesc_ShengjiLocalDataProtocol_2eproto();
  friend void protobuf_ShutdownFile_ShengjiLocalDataProtocol_2eproto();

  void InitAsDefaultInstance();
  static AccountInfo* default_instance_;
};
// -------------------------------------------------------------------

class AccountVector : public ::google::protobuf::Message {
 public:
  AccountVector();
  virtual ~AccountVector();

  AccountVector(const AccountVector& from);

  inline AccountVector& operator=(const AccountVector& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AccountVector& default_instance();

  void Swap(AccountVector* other);

  // implements Message ----------------------------------------------

  AccountVector* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AccountVector& from);
  void MergeFrom(const AccountVector& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .AccountInfo account_vector = 1;
  inline int account_vector_size() const;
  inline void clear_account_vector();
  static const int kAccountVectorFieldNumber = 1;
  inline const ::AccountInfo& account_vector(int index) const;
  inline ::AccountInfo* mutable_account_vector(int index);
  inline ::AccountInfo* add_account_vector();
  inline const ::google::protobuf::RepeatedPtrField< ::AccountInfo >&
      account_vector() const;
  inline ::google::protobuf::RepeatedPtrField< ::AccountInfo >*
      mutable_account_vector();

  // @@protoc_insertion_point(class_scope:AccountVector)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::AccountInfo > account_vector_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_ShengjiLocalDataProtocol_2eproto();
  friend void protobuf_AssignDesc_ShengjiLocalDataProtocol_2eproto();
  friend void protobuf_ShutdownFile_ShengjiLocalDataProtocol_2eproto();

  void InitAsDefaultInstance();
  static AccountVector* default_instance_;
};
// ===================================================================


// ===================================================================

// AccountInfo

// required string account_name = 1;
inline bool AccountInfo::has_account_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AccountInfo::set_has_account_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AccountInfo::clear_has_account_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AccountInfo::clear_account_name() {
  if (account_name_ != &::google::protobuf::internal::kEmptyString) {
    account_name_->clear();
  }
  clear_has_account_name();
}
inline const ::std::string& AccountInfo::account_name() const {
  return *account_name_;
}
inline void AccountInfo::set_account_name(const ::std::string& value) {
  set_has_account_name();
  if (account_name_ == &::google::protobuf::internal::kEmptyString) {
    account_name_ = new ::std::string;
  }
  account_name_->assign(value);
}
inline void AccountInfo::set_account_name(const char* value) {
  set_has_account_name();
  if (account_name_ == &::google::protobuf::internal::kEmptyString) {
    account_name_ = new ::std::string;
  }
  account_name_->assign(value);
}
inline void AccountInfo::set_account_name(const char* value, size_t size) {
  set_has_account_name();
  if (account_name_ == &::google::protobuf::internal::kEmptyString) {
    account_name_ = new ::std::string;
  }
  account_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AccountInfo::mutable_account_name() {
  set_has_account_name();
  if (account_name_ == &::google::protobuf::internal::kEmptyString) {
    account_name_ = new ::std::string;
  }
  return account_name_;
}
inline ::std::string* AccountInfo::release_account_name() {
  clear_has_account_name();
  if (account_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = account_name_;
    account_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AccountInfo::set_allocated_account_name(::std::string* account_name) {
  if (account_name_ != &::google::protobuf::internal::kEmptyString) {
    delete account_name_;
  }
  if (account_name) {
    set_has_account_name();
    account_name_ = account_name;
  } else {
    clear_has_account_name();
    account_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string account_password = 2;
inline bool AccountInfo::has_account_password() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AccountInfo::set_has_account_password() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AccountInfo::clear_has_account_password() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AccountInfo::clear_account_password() {
  if (account_password_ != &::google::protobuf::internal::kEmptyString) {
    account_password_->clear();
  }
  clear_has_account_password();
}
inline const ::std::string& AccountInfo::account_password() const {
  return *account_password_;
}
inline void AccountInfo::set_account_password(const ::std::string& value) {
  set_has_account_password();
  if (account_password_ == &::google::protobuf::internal::kEmptyString) {
    account_password_ = new ::std::string;
  }
  account_password_->assign(value);
}
inline void AccountInfo::set_account_password(const char* value) {
  set_has_account_password();
  if (account_password_ == &::google::protobuf::internal::kEmptyString) {
    account_password_ = new ::std::string;
  }
  account_password_->assign(value);
}
inline void AccountInfo::set_account_password(const char* value, size_t size) {
  set_has_account_password();
  if (account_password_ == &::google::protobuf::internal::kEmptyString) {
    account_password_ = new ::std::string;
  }
  account_password_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AccountInfo::mutable_account_password() {
  set_has_account_password();
  if (account_password_ == &::google::protobuf::internal::kEmptyString) {
    account_password_ = new ::std::string;
  }
  return account_password_;
}
inline ::std::string* AccountInfo::release_account_password() {
  clear_has_account_password();
  if (account_password_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = account_password_;
    account_password_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AccountInfo::set_allocated_account_password(::std::string* account_password) {
  if (account_password_ != &::google::protobuf::internal::kEmptyString) {
    delete account_password_;
  }
  if (account_password) {
    set_has_account_password();
    account_password_ = account_password;
  } else {
    clear_has_account_password();
    account_password_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string nick_name = 3;
inline bool AccountInfo::has_nick_name() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AccountInfo::set_has_nick_name() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AccountInfo::clear_has_nick_name() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AccountInfo::clear_nick_name() {
  if (nick_name_ != &::google::protobuf::internal::kEmptyString) {
    nick_name_->clear();
  }
  clear_has_nick_name();
}
inline const ::std::string& AccountInfo::nick_name() const {
  return *nick_name_;
}
inline void AccountInfo::set_nick_name(const ::std::string& value) {
  set_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    nick_name_ = new ::std::string;
  }
  nick_name_->assign(value);
}
inline void AccountInfo::set_nick_name(const char* value) {
  set_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    nick_name_ = new ::std::string;
  }
  nick_name_->assign(value);
}
inline void AccountInfo::set_nick_name(const char* value, size_t size) {
  set_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    nick_name_ = new ::std::string;
  }
  nick_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* AccountInfo::mutable_nick_name() {
  set_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    nick_name_ = new ::std::string;
  }
  return nick_name_;
}
inline ::std::string* AccountInfo::release_nick_name() {
  clear_has_nick_name();
  if (nick_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = nick_name_;
    nick_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void AccountInfo::set_allocated_nick_name(::std::string* nick_name) {
  if (nick_name_ != &::google::protobuf::internal::kEmptyString) {
    delete nick_name_;
  }
  if (nick_name) {
    set_has_nick_name();
    nick_name_ = nick_name;
  } else {
    clear_has_nick_name();
    nick_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required uint32 face_id = 4;
inline bool AccountInfo::has_face_id() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void AccountInfo::set_has_face_id() {
  _has_bits_[0] |= 0x00000008u;
}
inline void AccountInfo::clear_has_face_id() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void AccountInfo::clear_face_id() {
  face_id_ = 0u;
  clear_has_face_id();
}
inline ::google::protobuf::uint32 AccountInfo::face_id() const {
  return face_id_;
}
inline void AccountInfo::set_face_id(::google::protobuf::uint32 value) {
  set_has_face_id();
  face_id_ = value;
}

// required uint64 user_id = 5;
inline bool AccountInfo::has_user_id() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void AccountInfo::set_has_user_id() {
  _has_bits_[0] |= 0x00000010u;
}
inline void AccountInfo::clear_has_user_id() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void AccountInfo::clear_user_id() {
  user_id_ = GOOGLE_ULONGLONG(0);
  clear_has_user_id();
}
inline ::google::protobuf::uint64 AccountInfo::user_id() const {
  return user_id_;
}
inline void AccountInfo::set_user_id(::google::protobuf::uint64 value) {
  set_has_user_id();
  user_id_ = value;
}

// required uint32 vip_type = 6;
inline bool AccountInfo::has_vip_type() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void AccountInfo::set_has_vip_type() {
  _has_bits_[0] |= 0x00000020u;
}
inline void AccountInfo::clear_has_vip_type() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void AccountInfo::clear_vip_type() {
  vip_type_ = 0u;
  clear_has_vip_type();
}
inline ::google::protobuf::uint32 AccountInfo::vip_type() const {
  return vip_type_;
}
inline void AccountInfo::set_vip_type(::google::protobuf::uint32 value) {
  set_has_vip_type();
  vip_type_ = value;
}

// required uint32 vip_level = 7;
inline bool AccountInfo::has_vip_level() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void AccountInfo::set_has_vip_level() {
  _has_bits_[0] |= 0x00000040u;
}
inline void AccountInfo::clear_has_vip_level() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void AccountInfo::clear_vip_level() {
  vip_level_ = 0u;
  clear_has_vip_level();
}
inline ::google::protobuf::uint32 AccountInfo::vip_level() const {
  return vip_level_;
}
inline void AccountInfo::set_vip_level(::google::protobuf::uint32 value) {
  set_has_vip_level();
  vip_level_ = value;
}

// required uint32 vip_year_status = 8;
inline bool AccountInfo::has_vip_year_status() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void AccountInfo::set_has_vip_year_status() {
  _has_bits_[0] |= 0x00000080u;
}
inline void AccountInfo::clear_has_vip_year_status() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void AccountInfo::clear_vip_year_status() {
  vip_year_status_ = 0u;
  clear_has_vip_year_status();
}
inline ::google::protobuf::uint32 AccountInfo::vip_year_status() const {
  return vip_year_status_;
}
inline void AccountInfo::set_vip_year_status(::google::protobuf::uint32 value) {
  set_has_vip_year_status();
  vip_year_status_ = value;
}

// required uint32 head_frame_type = 9;
inline bool AccountInfo::has_head_frame_type() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void AccountInfo::set_has_head_frame_type() {
  _has_bits_[0] |= 0x00000100u;
}
inline void AccountInfo::clear_has_head_frame_type() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void AccountInfo::clear_head_frame_type() {
  head_frame_type_ = 0u;
  clear_has_head_frame_type();
}
inline ::google::protobuf::uint32 AccountInfo::head_frame_type() const {
  return head_frame_type_;
}
inline void AccountInfo::set_head_frame_type(::google::protobuf::uint32 value) {
  set_has_head_frame_type();
  head_frame_type_ = value;
}

// -------------------------------------------------------------------

// AccountVector

// repeated .AccountInfo account_vector = 1;
inline int AccountVector::account_vector_size() const {
  return account_vector_.size();
}
inline void AccountVector::clear_account_vector() {
  account_vector_.Clear();
}
inline const ::AccountInfo& AccountVector::account_vector(int index) const {
  return account_vector_.Get(index);
}
inline ::AccountInfo* AccountVector::mutable_account_vector(int index) {
  return account_vector_.Mutable(index);
}
inline ::AccountInfo* AccountVector::add_account_vector() {
  return account_vector_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::AccountInfo >&
AccountVector::account_vector() const {
  return account_vector_;
}
inline ::google::protobuf::RepeatedPtrField< ::AccountInfo >*
AccountVector::mutable_account_vector() {
  return &account_vector_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ShengjiLocalDataProtocol_2eproto__INCLUDED
