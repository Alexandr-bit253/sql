#include <Wt/Dbo/Dbo.h>
#include <Wt/WDateTime.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Dbo/backend/Postgres.h>

namespace dbo = Wt::Dbo;

class Publisher;
class Book;
class Shop;
class Stock;
class Sale;

typedef dbo::collection<dbo::ptr<Book>> Books;
class Publisher
{
public:
    std::string name;
    Books books;

    template <typename Action>
    void persist(Action &a)
    {
        dbo::field(a, name, "name");
        dbo::hasMany(a, books, dbo::ManyToOne, "publisher");
    }
};

typedef dbo::collection<dbo::ptr<Stock>> Stocks;
class Book
{
public:
    std::string title;
    dbo::ptr<Publisher> publisher;
    Stocks stocks;

    template <typename Action>
    void persist(Action &a)
    {
        dbo::field(a, title, "title");
        dbo::belongsTo(a, publisher, "publisher");
        dbo::hasMany(a, stocks, dbo::ManyToOne, "book");
    }
};

typedef dbo::collection<dbo::ptr<Stock>> ShopStocks;
class Shop
{
public:
    std::string name;
    ShopStocks stocks;

    template <typename Action>
    void persist(Action &a)
    {
        dbo::field(a, name, "name");
        dbo::hasMany(a, stocks, dbo::ManyToOne, "shop");
    }
};

typedef dbo::collection<dbo::ptr<Sale>> Sales;
class Stock
{
public:
    int count;
    dbo::ptr<Book> book;
    dbo::ptr<Shop> shop;
    Sales sales;

    template <typename Action>
    void persist(Action &a)
    {
        dbo::field(a, count, "count");
        dbo::belongsTo(a, book, "book");
        dbo::belongsTo(a, shop, "shop");
        dbo::hasMany(a, sales, dbo::ManyToOne, "stock");
    }
};

class Sale
{
public:
    double price;
    Wt::WDateTime dateSale;
    int count;
    dbo::ptr<Stock> stock;

    template <typename Action>
    void persist(Action &a)
    {
        dbo::field(a, price, "price");
        dbo::field(a, dateSale, "date_sale");
        dbo::field(a, count, "count");
        dbo::belongsTo(a, stock, "stock");
    }
};