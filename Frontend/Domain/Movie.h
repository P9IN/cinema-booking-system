#pragma once
#include <string>

namespace Domain {
    class Movie {
    public:
        Movie(std::string name, int age, std::string genre, double rating)
            : name_(std::move(name))
            , age_(age)
            , genre_(std::move(genre))
            , rating_(rating) {
        }

        // Default constructor
        Movie() : name_(""), age_(0), genre_(""), rating_(0.0) {}

        // Getters
        const std::string& getName() const { return name_; }
        int getAge() const { return age_; }
        const std::string& getGenre() const { return genre_; }
        double getRating() const { return rating_; }

        // Setters
        void setName(const std::string& name) { name_ = name; }
        void setAge(int age) { age_ = age; }
        void setGenre(const std::string& genre) { genre_ = genre; }
        void setRating(double rating) { rating_ = rating; }

    private:
        std::string name_;
        int age_;
        std::string genre_;
        double rating_;
    };
}