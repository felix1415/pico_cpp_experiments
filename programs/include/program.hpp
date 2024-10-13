class Program
{
    Program();
    virtual void run() = 0;

    protected:
        virtual void setup() = 0;
        virtual void teardown() = 0;
};