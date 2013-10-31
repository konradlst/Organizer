#ifndef UNIFIEDFACTORY_H
#define UNIFIEDFACTORY_H

#include <QHash>
#include <QString>

//! \class UnifiedFactory<class Base>
//! \brief Универсальная шаблонная Фабрика объектов по зарегистрированому имени класса.
//! Конструируемые объекты должны иметь общего предка \param Base

template<class Base>
class UnifiedFactory
{
public:
    UnifiedFactory() {}
    ~UnifiedFactory() { qDeleteAll(m_builders); }
    //! Регистрирует класс T по имени \param name
    //! Если такое имя класса уже зарегистрировано - выбрасывает ASSERT
    template<class T>
    void registerClass(const QString &name)
    {
        delete m_builders.value(name);
        m_builders.insert(name, new Builder<T>());
    }
    //! Создает объект по зарегистрированому имени \param name
    //! Возвращает 0 если такой класс не зарегистрирован
    Base* build(const QString &name) const
    {
        BaseBuilder *builder = m_builders.value(name);
        if (builder)
            return builder->build();
        return 0;
    }

private:
    //! Абстрактный класс-строитель
    class BaseBuilder
    {
    public:
        virtual Base* build() const = 0;
    };
    //! Шаблонный строитель объектов класса Т
    template<class T>
    class Builder : public BaseBuilder
    {
    public:
        virtual Base* build() const { return new T(); }
    };
    typedef QHash<QString, BaseBuilder*> Builders;
    //! хранилище объектов-строителей
    Builders m_builders;
};

//! \macro UNIFIED_FACTORY
//! \brief Макрос для добавления статической фабрики-члена к базовому классу \param BaseType конструируемых наследников

#define UNIFIED_FACTORY(BaseType) \
    static UnifiedFactory<BaseType>* factory() \
    { \
        static UnifiedFactory<BaseType> s_factory; \
        return &s_factory; \
    } \
    template<class T> \
    class AutoRegistrer \
    { \
    public: \
        AutoRegistrer(const QString &name) { factory()->registerClass<T>(name); } \
    }; \

//! \macro UF_REGISTER_DERIVED_NAMED
//! \brief Макрос регистрации наследника по произвольному имени
//! в фабрике предка, объявленной макросом \macro UNIFIED_FACTORY

#define UF_REGISTER_DERIVED_NAMED(type, name) \
    static const type::AutoRegistrer<type> type##Registrator(name);

// not used?
// //! \macro UF_REGISTER_DERIVED
// //! \brief Макрос регистрации наследника по имени класса
// //! в фабрике предка, объявленной макросом \macro UNIFIED_FACTORY
// #define UF_REGISTER_DERIVED(type) UF_REGISTER_DERIVED_NAMED(type, #type)

// example
// init: UNIFIED_FACTORY(className) - in public section abstract class
// init: UF_REGISTER_DERIVED_NAMED(concreteClassName, BaseClassNamespace::StringWithNameConcreteClass)
// using: BaseClassName::factory()->build(StringWithNameConcreteClass)

#endif // UNIFIEDFACTORY_H
