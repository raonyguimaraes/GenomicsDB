// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: genomicsdb_callsets_mapping.proto

#ifndef PROTOBUF_genomicsdb_5fcallsets_5fmapping_2eproto__INCLUDED
#define PROTOBUF_genomicsdb_5fcallsets_5fmapping_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000002 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/map.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_genomicsdb_5fcallsets_5fmapping_2eproto();
void protobuf_AssignDesc_genomicsdb_5fcallsets_5fmapping_2eproto();
void protobuf_ShutdownFile_genomicsdb_5fcallsets_5fmapping_2eproto();

class CallsetMappingPB;
class SampleIDToTileDBIDMap;

// ===================================================================

class SampleIDToTileDBIDMap : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:SampleIDToTileDBIDMap) */ {
 public:
  SampleIDToTileDBIDMap();
  virtual ~SampleIDToTileDBIDMap();

  SampleIDToTileDBIDMap(const SampleIDToTileDBIDMap& from);

  inline SampleIDToTileDBIDMap& operator=(const SampleIDToTileDBIDMap& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SampleIDToTileDBIDMap& default_instance();

  void Swap(SampleIDToTileDBIDMap* other);

  // implements Message ----------------------------------------------

  inline SampleIDToTileDBIDMap* New() const { return New(NULL); }

  SampleIDToTileDBIDMap* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SampleIDToTileDBIDMap& from);
  void MergeFrom(const SampleIDToTileDBIDMap& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(SampleIDToTileDBIDMap* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string sample_name = 1;
  bool has_sample_name() const;
  void clear_sample_name();
  static const int kSampleNameFieldNumber = 1;
  const ::std::string& sample_name() const;
  void set_sample_name(const ::std::string& value);
  void set_sample_name(const char* value);
  void set_sample_name(const char* value, size_t size);
  ::std::string* mutable_sample_name();
  ::std::string* release_sample_name();
  void set_allocated_sample_name(::std::string* sample_name);

  // required int64 tiledb_row_index = 2;
  bool has_tiledb_row_index() const;
  void clear_tiledb_row_index();
  static const int kTiledbRowIndexFieldNumber = 2;
  ::google::protobuf::int64 tiledb_row_index() const;
  void set_tiledb_row_index(::google::protobuf::int64 value);

  // required int32 idx_in_file = 3;
  bool has_idx_in_file() const;
  void clear_idx_in_file();
  static const int kIdxInFileFieldNumber = 3;
  ::google::protobuf::int32 idx_in_file() const;
  void set_idx_in_file(::google::protobuf::int32 value);

  // optional string stream_name = 4;
  bool has_stream_name() const;
  void clear_stream_name();
  static const int kStreamNameFieldNumber = 4;
  const ::std::string& stream_name() const;
  void set_stream_name(const ::std::string& value);
  void set_stream_name(const char* value);
  void set_stream_name(const char* value, size_t size);
  ::std::string* mutable_stream_name();
  ::std::string* release_stream_name();
  void set_allocated_stream_name(::std::string* stream_name);

  // @@protoc_insertion_point(class_scope:SampleIDToTileDBIDMap)
 private:
  inline void set_has_sample_name();
  inline void clear_has_sample_name();
  inline void set_has_tiledb_row_index();
  inline void clear_has_tiledb_row_index();
  inline void set_has_idx_in_file();
  inline void clear_has_idx_in_file();
  inline void set_has_stream_name();
  inline void clear_has_stream_name();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr sample_name_;
  ::google::protobuf::int64 tiledb_row_index_;
  ::google::protobuf::internal::ArenaStringPtr stream_name_;
  ::google::protobuf::int32 idx_in_file_;
  friend void  protobuf_AddDesc_genomicsdb_5fcallsets_5fmapping_2eproto();
  friend void protobuf_AssignDesc_genomicsdb_5fcallsets_5fmapping_2eproto();
  friend void protobuf_ShutdownFile_genomicsdb_5fcallsets_5fmapping_2eproto();

  void InitAsDefaultInstance();
  static SampleIDToTileDBIDMap* default_instance_;
};
// -------------------------------------------------------------------

class CallsetMappingPB : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:CallsetMappingPB) */ {
 public:
  CallsetMappingPB();
  virtual ~CallsetMappingPB();

  CallsetMappingPB(const CallsetMappingPB& from);

  inline CallsetMappingPB& operator=(const CallsetMappingPB& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CallsetMappingPB& default_instance();

  void Swap(CallsetMappingPB* other);

  // implements Message ----------------------------------------------

  inline CallsetMappingPB* New() const { return New(NULL); }

  CallsetMappingPB* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CallsetMappingPB& from);
  void MergeFrom(const CallsetMappingPB& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(CallsetMappingPB* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------


  // accessors -------------------------------------------------------

  // map<string, .SampleIDToTileDBIDMap> callset_map = 1;
  int callset_map_size() const;
  void clear_callset_map();
  static const int kCallsetMapFieldNumber = 1;
  const ::google::protobuf::Map< ::std::string, ::SampleIDToTileDBIDMap >&
      callset_map() const;
  ::google::protobuf::Map< ::std::string, ::SampleIDToTileDBIDMap >*
      mutable_callset_map();

  // @@protoc_insertion_point(class_scope:CallsetMappingPB)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  typedef ::google::protobuf::internal::MapEntryLite<
      ::std::string, ::SampleIDToTileDBIDMap,
      ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
      ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
      0 >
      CallsetMappingPB_CallsetMapEntry;
  ::google::protobuf::internal::MapField<
      ::std::string, ::SampleIDToTileDBIDMap,
      ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
      ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
      0 > callset_map_;
  friend void  protobuf_AddDesc_genomicsdb_5fcallsets_5fmapping_2eproto();
  friend void protobuf_AssignDesc_genomicsdb_5fcallsets_5fmapping_2eproto();
  friend void protobuf_ShutdownFile_genomicsdb_5fcallsets_5fmapping_2eproto();

  void InitAsDefaultInstance();
  static CallsetMappingPB* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// SampleIDToTileDBIDMap

// required string sample_name = 1;
inline bool SampleIDToTileDBIDMap::has_sample_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SampleIDToTileDBIDMap::set_has_sample_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SampleIDToTileDBIDMap::clear_has_sample_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SampleIDToTileDBIDMap::clear_sample_name() {
  sample_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_sample_name();
}
inline const ::std::string& SampleIDToTileDBIDMap::sample_name() const {
  // @@protoc_insertion_point(field_get:SampleIDToTileDBIDMap.sample_name)
  return sample_name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void SampleIDToTileDBIDMap::set_sample_name(const ::std::string& value) {
  set_has_sample_name();
  sample_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SampleIDToTileDBIDMap.sample_name)
}
inline void SampleIDToTileDBIDMap::set_sample_name(const char* value) {
  set_has_sample_name();
  sample_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SampleIDToTileDBIDMap.sample_name)
}
inline void SampleIDToTileDBIDMap::set_sample_name(const char* value, size_t size) {
  set_has_sample_name();
  sample_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SampleIDToTileDBIDMap.sample_name)
}
inline ::std::string* SampleIDToTileDBIDMap::mutable_sample_name() {
  set_has_sample_name();
  // @@protoc_insertion_point(field_mutable:SampleIDToTileDBIDMap.sample_name)
  return sample_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* SampleIDToTileDBIDMap::release_sample_name() {
  // @@protoc_insertion_point(field_release:SampleIDToTileDBIDMap.sample_name)
  clear_has_sample_name();
  return sample_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void SampleIDToTileDBIDMap::set_allocated_sample_name(::std::string* sample_name) {
  if (sample_name != NULL) {
    set_has_sample_name();
  } else {
    clear_has_sample_name();
  }
  sample_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), sample_name);
  // @@protoc_insertion_point(field_set_allocated:SampleIDToTileDBIDMap.sample_name)
}

// required int64 tiledb_row_index = 2;
inline bool SampleIDToTileDBIDMap::has_tiledb_row_index() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SampleIDToTileDBIDMap::set_has_tiledb_row_index() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SampleIDToTileDBIDMap::clear_has_tiledb_row_index() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SampleIDToTileDBIDMap::clear_tiledb_row_index() {
  tiledb_row_index_ = GOOGLE_LONGLONG(0);
  clear_has_tiledb_row_index();
}
inline ::google::protobuf::int64 SampleIDToTileDBIDMap::tiledb_row_index() const {
  // @@protoc_insertion_point(field_get:SampleIDToTileDBIDMap.tiledb_row_index)
  return tiledb_row_index_;
}
inline void SampleIDToTileDBIDMap::set_tiledb_row_index(::google::protobuf::int64 value) {
  set_has_tiledb_row_index();
  tiledb_row_index_ = value;
  // @@protoc_insertion_point(field_set:SampleIDToTileDBIDMap.tiledb_row_index)
}

// required int32 idx_in_file = 3;
inline bool SampleIDToTileDBIDMap::has_idx_in_file() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SampleIDToTileDBIDMap::set_has_idx_in_file() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SampleIDToTileDBIDMap::clear_has_idx_in_file() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SampleIDToTileDBIDMap::clear_idx_in_file() {
  idx_in_file_ = 0;
  clear_has_idx_in_file();
}
inline ::google::protobuf::int32 SampleIDToTileDBIDMap::idx_in_file() const {
  // @@protoc_insertion_point(field_get:SampleIDToTileDBIDMap.idx_in_file)
  return idx_in_file_;
}
inline void SampleIDToTileDBIDMap::set_idx_in_file(::google::protobuf::int32 value) {
  set_has_idx_in_file();
  idx_in_file_ = value;
  // @@protoc_insertion_point(field_set:SampleIDToTileDBIDMap.idx_in_file)
}

// optional string stream_name = 4;
inline bool SampleIDToTileDBIDMap::has_stream_name() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void SampleIDToTileDBIDMap::set_has_stream_name() {
  _has_bits_[0] |= 0x00000008u;
}
inline void SampleIDToTileDBIDMap::clear_has_stream_name() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void SampleIDToTileDBIDMap::clear_stream_name() {
  stream_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_stream_name();
}
inline const ::std::string& SampleIDToTileDBIDMap::stream_name() const {
  // @@protoc_insertion_point(field_get:SampleIDToTileDBIDMap.stream_name)
  return stream_name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void SampleIDToTileDBIDMap::set_stream_name(const ::std::string& value) {
  set_has_stream_name();
  stream_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SampleIDToTileDBIDMap.stream_name)
}
inline void SampleIDToTileDBIDMap::set_stream_name(const char* value) {
  set_has_stream_name();
  stream_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SampleIDToTileDBIDMap.stream_name)
}
inline void SampleIDToTileDBIDMap::set_stream_name(const char* value, size_t size) {
  set_has_stream_name();
  stream_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SampleIDToTileDBIDMap.stream_name)
}
inline ::std::string* SampleIDToTileDBIDMap::mutable_stream_name() {
  set_has_stream_name();
  // @@protoc_insertion_point(field_mutable:SampleIDToTileDBIDMap.stream_name)
  return stream_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* SampleIDToTileDBIDMap::release_stream_name() {
  // @@protoc_insertion_point(field_release:SampleIDToTileDBIDMap.stream_name)
  clear_has_stream_name();
  return stream_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void SampleIDToTileDBIDMap::set_allocated_stream_name(::std::string* stream_name) {
  if (stream_name != NULL) {
    set_has_stream_name();
  } else {
    clear_has_stream_name();
  }
  stream_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), stream_name);
  // @@protoc_insertion_point(field_set_allocated:SampleIDToTileDBIDMap.stream_name)
}

// -------------------------------------------------------------------

// CallsetMappingPB

// map<string, .SampleIDToTileDBIDMap> callset_map = 1;
inline int CallsetMappingPB::callset_map_size() const {
  return callset_map_.size();
}
inline void CallsetMappingPB::clear_callset_map() {
  callset_map_.Clear();
}
inline const ::google::protobuf::Map< ::std::string, ::SampleIDToTileDBIDMap >&
CallsetMappingPB::callset_map() const {
  // @@protoc_insertion_point(field_map:CallsetMappingPB.callset_map)
  return callset_map_.GetMap();
}
inline ::google::protobuf::Map< ::std::string, ::SampleIDToTileDBIDMap >*
CallsetMappingPB::mutable_callset_map() {
  // @@protoc_insertion_point(field_mutable_map:CallsetMappingPB.callset_map)
  return callset_map_.MutableMap();
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_genomicsdb_5fcallsets_5fmapping_2eproto__INCLUDED
