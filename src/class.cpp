#include "class.h"
#include <string.h>


/// @brief calculate the space occupation of a string 
/// @author Cillian Young
/// @param str  I- string
/// @return space occupation
int spaceOccupation(std::string str)
{
    char *a;
    a = new char[str.size() + 1];
    strcpy(a, str.c_str());
    int count_chinese = 0, count_ch = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (a[i] < 0)
            count_chinese++;
        else
            count_ch++;
    }
    int total_length = count_chinese / 3 * 2 + count_ch;
    return total_length;
}

/// @brief
/// @author Cillian Young
/// @param length       I- total length of a cell of the table
/// @param table_value  I- table value
/// @param mid_ch       I- middle char
/// @param end_ch       I- end char
/// @param if_end       I- whether the end of a line
/// @param align        I- align
void coutTableContentComponent(int length, std::string table_value, char mid_ch, char end_ch, bool if_end, TABLE_ALIGN align)
{
    int table_value_length = spaceOccupation(table_value);
    int mid_ch_length = length - table_value_length;
    //assert(mid_ch_length > 0);
    if (0 == align)
    {
        std::cout << table_value;
        for (int i = 0; i < mid_ch_length - 1; i++)
        {
            printf("%c", mid_ch);
        }
        printf("%c", end_ch);
    }
    else if (1 == align)
    {
        for (int i = 0; i < mid_ch_length / 2; i++)
        {
            printf("%c", mid_ch);
        }
        std::cout << table_value;
        for (int i = 0; i < mid_ch_length - mid_ch_length / 2 - 1; i++)
        {
            printf("%c", mid_ch);
        }
        printf("%c", end_ch);
    }
    else if (2 == align)
    {
        for (int i = 0; i < mid_ch_length - 1; i++)
        {
            printf("%c", mid_ch);
        }
        std::cout << table_value;
        printf("%c", end_ch);
    }
    if (if_end)
    {
        printf("\n");
    }
}


/// @brief
/// @author Cillian Young
/// @param length I- total cell length of the table
/// @param mid_ch I- middle char
/// @param end_ch I- end char
/// @param if_end I- whether the end of a line
void coutTableLineComponent(int length, char mid_ch, char end_ch, bool if_end)
{
    // 参数检查??
    for (int i = 0; i < length - 1; i++)
    {
        printf("%c", mid_ch);
    }
    printf("%c", end_ch);
    if (if_end)
    {
        printf("\n");
    }
}


void coutLine(std::vector<int> length, char start, char mid_ch, char end_ch)
{
    printf("%c", start);
    for (int i = 0; i < length.size() - 1; i++)
    {
        coutTableLineComponent(length[i], mid_ch, end_ch, false);
    }
    coutTableLineComponent(length[length.size() - 1], mid_ch, end_ch, true);
}


void TableMessage::messageShowInTable(TABLE_ALIGN align)
{
    // 1. calculate table height
    int row = value_v.getLine().size();
    int length_k = 0, length_v = 0, length_head = 0;
    if(head_on)
    {
        length_head = spaceOccupation(head_v.getLine()[0]);
    }
    for (int i = 0; i < row; i++)
    {
        int tmp_k_len = spaceOccupation(key_v.getLine()[i]);
        if (tmp_k_len > length_k)
        {
            length_k = tmp_k_len;
        }
        int tmp_v_len = spaceOccupation(value_v.getLine()[i]);
        if (tmp_v_len > length_v)
        {
            length_v = tmp_v_len;
        }
    }
    length_k += 1;
    length_v += 1;
    length_head += 1;
    if(length_head > length_v + length_k)
    {
        length_k = (length_head - length_v - length_k) / 2;
        length_v = length_head - length_k;
    }
    // 2. display  table content in format of TABLE_ALIGN
    int min_cell_len = 20;
    if (length_v >= 0 && length_k >= 0 && row > 0)
    {
        if (length_v < min_cell_len)
            length_v = min_cell_len;
        if (length_k < min_cell_len)
            length_k = min_cell_len;
        // display table head
        if(head_on)
        {
            std::vector<int> head_len;
            head_len.push_back(length_k + length_v);
            coutLine(head_len, start_ch, mid_ch, end_ch);
            printf("%c", split_ch);
            coutTableContentComponent(head_len[0], head_v.getLine()[0], fill_ch, split_ch, true, align);            
        }

        std::vector<int> column_len;
        column_len.push_back(length_k);
        column_len.push_back(length_v);
        for (int i = 0; i < row; i++)
        {
            coutLine(column_len, start_ch, mid_ch, end_ch);
            printf("%c", split_ch);
            coutTableContentComponent(length_k, key_v.getLine()[i], fill_ch, split_ch, false, align);
            coutTableContentComponent(length_v, value_v.getLine()[i], fill_ch, split_ch, true, align);
        }
        coutLine(column_len, start_ch, mid_ch, end_ch);
    }
}

TableLine& TableMessage::key()  
{
    linePtr = &key_v;
    return *linePtr;
}

TableLine& TableMessage::head()  
{
    if(1 != head_on)
        head_on = 1;
    else
    {
        std::cout << "there is only one head, but you init two! Delete the second \'mes.head() <<\'" << std::endl << "aborting..." << std::endl;
        abort();
    }
    linePtr = &head_v;
    return *linePtr;
}
TableLine& TableMessage::value()  
{
    linePtr = &value_v;
    return *linePtr;
}

void* TableMessage::endl()
{
    void* ret = linePtr->end();
    return ret;
}

TableMessage::TableMessage() : start_ch('+'),mid_ch('-'),end_ch('+'),split_ch('|'), fill_ch(' ')
{
    head_on = 0;
};
TableMessage::TableMessage(char start_sym, char end_sym, char mid_sym, char split_sym, char fill_sym)
{
    head_on = 0;
    start_ch = start_sym;
    mid_ch = mid_sym;
    end_ch = end_sym;
    split_ch = split_sym;
    fill_ch = fill_sym;    
};


TableMessage::~TableMessage()
{
}

//////////////////////////////////////////////////////////////////////
TableLine::TableLine(/* args */)
{
    end_line = 0;
    legal_line_op = 0;
}
TableLine& TableLine::operator<<(const std::string str)
{
    tmp_str += str;
    return *this;
}

TableLine& TableLine::operator<<(const float data)
{
    std::string str = std::to_string(data);
    tmp_str += str;
    return *this;
}

TableLine& TableLine::operator<<(const double data)
{
    std::string str = std::to_string(data);
    tmp_str += str;
    return *this;
}

TableLine& TableLine::operator<<(const int data)
{
    std::string str = std::to_string(data);
    tmp_str += str;
    return *this;
}

TableLine& TableLine::operator<<(void* line_op)
{
    if(legal_line_op != 1)
    {
        // 抛出异常 used for block illegal line operation
        std::cout << "error line operation func!" << std::endl << "aborting..." << std::endl;
        abort();
    }
    else
    {
        table_line.push_back(tmp_str);
        tmp_str = "";
        end_line = 0;
        legal_line_op = 0;
    }
    return *this;
}

bool& TableLine::getStatus()
{
    return end_line;
}

std::vector<std::string>& TableLine::getLine()
{
    return table_line;
}

void* TableLine::end()
{
    end_line = 1;
    legal_line_op = 1;
    return nullptr;
}
TableLine::~TableLine()
{

}
