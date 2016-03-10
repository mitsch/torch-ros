#ifndef raw_message_h
#define raw_message_h

class RawMessage {
public:
  RawMessage()
    : num_bytes(0) {
  }

  RawMessage(size_t length)
    : buffer(new uint8_t[length])
    , num_bytes(length)
  {
  }

  void copyFrom(uint8_t *source, size_t length) {
    buffer = boost::shared_array<uint8_t>(new uint8_t[length]);
    memcpy(buffer.get(), source, length);
    this->num_bytes = length;
  }

  size_t get_length() const {
    return num_bytes;
  }

  const boost::shared_array<uint8_t>& get_buffer() const {
    return buffer;
  }

private:
  size_t num_bytes;
  boost::shared_array<uint8_t> buffer;
};

namespace ros {
namespace serialization {

template<>
inline SerializedMessage serializeMessage(const RawMessage &message)
{
  return SerializedMessage(message.get_buffer(), message.get_length());
}

}   // namespace serialization
}   // namespace ros

#endif    // raw_message_h