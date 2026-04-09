#pragma once
#include <string>
#include <chrono>
#include "Movie.h"

namespace Domain {
    class Session {
    public:
        Session(int id, Movie movie, std::string date, double price, int availableSeats = 30)
            : id_(id)
            , movie_(std::move(movie))
            , date_(std::move(date))
            , price_(price)
            , availableSeats_(availableSeats) {
        }

        // Default constructor
        Session() : id_(0), movie_(), date_(""), price_(0.0), availableSeats_(0) {}

        // Getters
        int getId() const { return id_; }
        const Movie& getMovie() const { return movie_; }
        const std::string& getDate() const { return date_; }
        double getPrice() const { return price_; }
        int getAvailableSeats() const { return availableSeats_; }

        // Setters
        void setId(int id) { id_ = id; }
        void setMovie(const Movie& movie) { movie_ = movie; }
        void setDate(const std::string& date) { date_ = date; }
        void setPrice(double price) { price_ = price; }
        void setAvailableSeats(int seats) { availableSeats_ = seats; }

        // Business logic
        bool hasAvailableSeats() const { return availableSeats_ > 0; }
        void decrementSeats() { if (availableSeats_ > 0) --availableSeats_; }

    private:
        int id_;
        Movie movie_;
        std::string date_;
        double price_;
        int availableSeats_;
    };
}