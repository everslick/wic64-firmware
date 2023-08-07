#ifndef WIC64_SERVER_H
#define WIC64_SERVER_H

#include "command.h"

namespace WiC64 {
    class Server : public Command {
        public:
            static const char* TAG;

            using Command::Command;
            const char* describe(void);
            void execute(void);
    };
}
#endif // WIC64_SERVER_H
