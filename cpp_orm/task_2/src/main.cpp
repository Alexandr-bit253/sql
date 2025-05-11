#include <iostream>
#include <memory>

#include "orm.hpp"

namespace dbo = Wt::Dbo;

void createData(dbo::Session &session)
{
    Wt::Dbo::Transaction transaction{session};

    // Publisher
    std::unique_ptr<Publisher> pub1Ptr{new Publisher()};
    pub1Ptr->name = "O'Reilly";
    dbo::ptr<Publisher> pub1 = session.add(std::move(pub1Ptr));

    std::unique_ptr<Publisher> pub2Ptr{new Publisher()};
    pub2Ptr->name = "Manning publications";
    dbo::ptr<Publisher> pub2 = session.add(std::move(pub2Ptr));

    // Book
    std::unique_ptr<Book> book1Ptr{new Book()};
    book1Ptr->title = "C++ best practices";
    book1Ptr->publisher = pub1;
    dbo::ptr<Book> book1 = session.add(std::move(book1Ptr));

    std::unique_ptr<Book> book2Ptr{new Book()};
    book2Ptr->title = "Effective modern c++";
    book2Ptr->publisher = pub1;
    dbo::ptr<Book> book2 = session.add(std::move(book2Ptr));

    std::unique_ptr<Book> book3Ptr{new Book()};
    book3Ptr->title = "Hands-on docker for c++ developers";
    book3Ptr->publisher = pub2;
    dbo::ptr<Book> book3 = session.add(std::move(book3Ptr));

    // Shop
    std::unique_ptr<Shop> shop1Ptr{new Shop()};
    shop1Ptr->name = "BookStore A";
    dbo::ptr<Shop> shop1 = session.add(std::move(shop1Ptr));

    std::unique_ptr<Shop> shop2Ptr{new Shop()};
    shop2Ptr->name = "Tech Books Shop";
    dbo::ptr<Shop> shop2 = session.add(std::move(shop2Ptr));

    // Stock
    std::unique_ptr<Stock> stock1Ptr{new Stock()};
    stock1Ptr->book = book1;
    stock1Ptr->shop = shop1;
    stock1Ptr->count = 10;
    dbo::ptr<Stock> stock1 = session.add(std::move(stock1Ptr));

    std::unique_ptr<Stock> stock2Ptr{new Stock()};
    stock2Ptr->book = book2;
    stock2Ptr->shop = shop1;
    stock2Ptr->count = 5;
    dbo::ptr<Stock> stock2 = session.add(std::move(stock2Ptr));

    std::unique_ptr<Stock> stock3Ptr{new Stock()};
    stock3Ptr->book = book3;
    stock3Ptr->shop = shop2;
    stock3Ptr->count = 8;
    dbo::ptr<Stock> stock3 = session.add(std::move(stock3Ptr));

    // Sale
    std::unique_ptr<Sale> sale1Ptr{new Sale()};
    sale1Ptr->stock = stock1;
    sale1Ptr->price = 29.99;
    sale1Ptr->dateSale = Wt::WDateTime::currentDateTime().addDays(-10);
    sale1Ptr->count = 1;
    session.add(std::move(sale1Ptr));

    std::unique_ptr<Sale> sale2Ptr{new Sale()};
    sale2Ptr->stock = stock1;
    sale2Ptr->price = 24.99;
    sale2Ptr->dateSale = Wt::WDateTime::currentDateTime().addDays(-5);
    sale2Ptr->count = 2;
    session.add(std::move(sale2Ptr));

    std::unique_ptr<Sale> sale3Ptr{new Sale()};
    sale3Ptr->stock = stock2;
    sale3Ptr->price = 39.99;
    sale3Ptr->dateSale = Wt::WDateTime::currentDateTime().addDays(-3);
    sale3Ptr->count = 1;
    session.add(std::move(sale3Ptr));

    std::unique_ptr<Sale> sale4Ptr{new Sale()};
    sale4Ptr->stock = stock3;
    sale4Ptr->price = 49.99;
    sale4Ptr->dateSale = Wt::WDateTime::currentDateTime().addDays(-1);
    sale4Ptr->count = 3;
    session.add(std::move(sale4Ptr));

    transaction.commit();
}

int main()
{
    try
    {
        dbo::Session session;
        session.mapClass<Publisher>("publisher");
        session.mapClass<Book>("book");
        session.mapClass<Shop>("shop");
        session.mapClass<Stock>("stock");
        session.mapClass<Sale>("sale");

        const char *host = std::getenv("DB_HOST");
        const char *port = std::getenv("DB_PORT");
        const char *db = std::getenv("POSTGRES_DB");
        const char *user = std::getenv("POSTGRES_USER");
        const char *pass = std::getenv("POSTGRES_PASSWORD");
        std::string connStr = "host=" + std::string(host ? host : "localhost") +
                              " port=" + std::string(port ? port : "5432") +
                              " dbname=" + std::string(db ? db : "wtdbo_db") +
                              " user=" + std::string(user ? user : "wtuser") +
                              " password=" + std::string(pass ? pass : "wtpass");
        auto conn = std::make_unique<dbo::backend::Postgres>(connStr);
        session.setConnection(std::move(conn));

        session.createTables();
        createData(session);
    }
    catch (std::exception &e)
    {
    }

    return 0;
}