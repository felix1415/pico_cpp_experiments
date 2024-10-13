#include <atomic>

class Program
{
    public:
        Program() = default;
        virtual ~Program() {}
        virtual void run() = 0;
        void stop() { mRunning.store(false); }

    protected:
        std::atomic<bool> mRunning {false};        
};