class DecodeException {
public:
    virtual const char* what() const throw() {
        return "Exception during decoding!";
    }
};