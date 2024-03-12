// This is a file that you can edit as per your needs!
#include "./include/rohanasan.h"

const char* myhandle(struct request req)
{
    if (eql(req.method, "GET")) {
        if (eql(req.path, "/"))
            return send_file(default_html_header, "./html/index.html");
        if (eql(req.path, "/health"))
            return send_http_response(default_html_header, "<h1>Website is active and working!</h1>");
        else return send_404();
    } else {
        return send_404();
    }
}

int main()
{
    printf("Listening at http://localhost:8080\n");
    init(8080);
    serve(myhandle);
}
