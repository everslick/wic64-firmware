#ifndef WIC64_HTTP_H
#define WIC64_HTTP_H

#include "command.h"
#include "data.h"
#include "WString.h"

namespace WiC64 {
    class Http : public Command {
        public: static const char* TAG;
        private:
            bool m_isProgramFile = false;

        public:
            using Command::Command;
            const char* describe(void);
            bool isProgramFile(void) { return m_isProgramFile; }

            void encode(String& url);
            void sanitize(String& url);
            void analyze(const String& url);
            void expand(String& url);

            void execute(void);
            void get(void);
            void post(void);

            void adjustResponseSizeForProgramFiles(void);
            void handleSettingChangeRequestFromServer(void);

            void responseReady(void);
    };
}
#endif // WIC64_HTTP_H