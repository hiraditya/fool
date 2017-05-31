/*
Given API: int Read4096(char* buf);

It reads data from a file and records the position so that the next time when it
is called it read the next 4k chars (or the rest of the file, whichever is
smaller) from the file.  The return is the number of chars read.

Todo: Use above API to Implement API "int Read(char* buf, int n)" which reads
any number of chars from the file.
*/

class reader {
  char ibuff[4096];
  char *buffer;
  int buff_size;

public:
  reader()
    : buffer(nullptr), buff_size(0)
  { }

  int read(char* buf, int n) {
    int n0 = n;
    if (n <= 0)
      return 0;
    int num = 0;

    if (n <= buff_size) {
      memcpy(buf, buffer, n);
      buff_size -= n;
      buffer += n;
      return n0;
    } else {
      // n > buff_size
      if (buff_size !=0) {
        int buf_off = 0;
        memcpy(buf, buffer, buff_size);
        buf_off += buff_size;
        buff_size = 0;
        buffer = buff;
        n -= buff_size;
      }
      while (n > 0) {
        int num_read = read4096(ibuff);
        if (num_read <= 0) {
          buffer = nullptr;
          buff_size = 0;
          return -1;
        }
        if (num_read >= n) {
          memcpy(buf + buf_off, buffer, n);
          buf_off += n;
          buff_size = num_read - n;
          buffer += n;
          return n0;
        } else {
          memcpy(buf + buf_off, buffer, num_read);
          buf_off += num_read;
          n -= num_read;
        }
      }
    }
    return num;
  }

};
