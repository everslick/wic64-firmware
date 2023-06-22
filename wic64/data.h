#ifndef WIC64_DATA_H
#define WIC64_DATA_H

#include <cstdint>

namespace WiC64 {
    class Data {
        private:
            bool m_allocated = false;
            uint8_t *m_data = NULL;
            uint16_t m_size = 0;

        public:
            Data();
            Data(uint16_t size);
            Data(uint8_t* data, uint16_t size);
            Data(const char* c_str);
            ~Data();

            bool isPresent(void);
            bool isEmpty(void);

            uint8_t* data() { return m_data; }
            uint16_t size() { return m_size; }
    };
}
#endif // WIC64_DATA_H