#include <utility>
#include <memory>
template <typename T>
class Singleton
{
private:
    std::unique_ptr<T> m_instance = nullptr;
    Singleton(Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;
    Singleton &operator=(Singleton &) = delete;
    Singleton() = delete;
    Singleton(T &&t)
        : m_instance(std::make_unique<T>(std::move(t))) {}

public:
    ~Singleton() {}

    inline static Singleton &init(T &&obj)
    {
        static Singleton<T> Singleton{std::move(obj)};
        return Singleton;
    }

    T *getInstance()
    {
        return m_instance.get();
    }
};
