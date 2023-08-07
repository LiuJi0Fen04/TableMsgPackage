#include <iostream>
#include <vector>

enum TABLE_ALIGN {TABLE_LEFT, TABLE_CENTER, TABLE_RIGHT};



class TableLine
{
private:
    /* data */
    std::vector<std::string> table_line;
    std::string tmp_str;
    bool end_line;
    bool legal_line_op;
public:
    TableLine(/* args */); // 设置为private
    TableLine& operator<<(const std::string str);
    TableLine& operator<<(const double str);
    TableLine& operator<<(const float str);
    TableLine& operator<<(const int str);
    TableLine& operator<<(void* line_op);
    // TableLine& operator<<(std::basic_ostream<class charT, class traits>& (*pf)(std::basic_ostream<class charT, class traits>&));
    std::vector<std::string>& getLine();
    bool& getStatus();
    void print()
    {
        for(int i = 0; i < table_line.size(); i++)
        {
            std::cout << "table_line: " << table_line[i] << std::endl;
        }
    }
    void* end();
    ~TableLine();
};


class TableMessage
{
private:
    /* data */
    TableLine key_v;
    TableLine value_v;
    TableLine head_v; // should be constricted based on the meassage
    TableLine* linePtr;

    /* border */
    char start_ch;
    char mid_ch;
    char end_ch;
    char split_ch;
    char fill_ch;

    /* status */
    bool head_on;
public:
    /**
     * used to init head of the table which can be init the way like std::cout;
     * if you don't use this function, head won't been shown
     */
    TableLine& head();
    /**
     * used to init key of the table which can be init the way like std::cout
     */
    TableLine& key();
    /**
     * used to init value of the table which can be init the way like std::cout
     */
    TableLine& value();
    /**
     * used to end the init of head, key and value
     */
    void* endl();
    /**
     * show table
     */
    void messageShowInTable(TABLE_ALIGN align = TABLE_CENTER);
    void clean()
    {

    }
    /**
     * default constructor
     */
    TableMessage();
    /**
     * constructor with parameter to specify the border of the table
     */
    TableMessage(char start_sym, char end_sym, char mid_sym, char split_sym, char fill_sym);

    ~TableMessage();
};

//ToDo:: func 'head' implement using singleton

