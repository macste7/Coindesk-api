/*
  
	MIT License

	Copyright (c) 2021 110 101 118 101 114 032 117 115 101 032 116 104 105 115 032 105 110 032 112 114 111 102 105 108 101

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
#ifndef coindesk_h
#define coindesk_h
#include <ArduinoJson.h>
#include <Client.h>
class Coindesk
{
private:
    Client *client;
    String web_api;
    String output;
    const char *web_host;
    bool debug;
    unsigned long timeout;
public:
    Coindesk(Client &client, const char *_web_host, String &_web_api,bool debug,unsigned long timeout);
    void make_request();
    ~Coindesk();
    char* time_updated();
public:

    struct Data
    {
        char *time_updated;
        char *time_updatedISO;
        char *time_updateduk;
        char *disclaimer;
        char *chartname;
    };
    struct USD
    {
        char *code;
        char *symbol;
        char *rate_char;
        char *description;
        float rate_float;
    };
    struct GBP
    {
        char *code;
        char *symbol;
        char *rate_char;
        char *description;
        float rate_float;
    };
    struct EUR
    {
        char *code;
        char *symbol;
        char *rate_char;
        char *description;
        float rate_float;
    };
    USD usd;
    GBP gbp;
    EUR eur;
    Data data;

};
#endif