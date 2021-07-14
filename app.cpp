#include <gtk/gtk.h>

#include <webkit2/webkit2.h>



static void destroyWindowCb(GtkWidget* widget, GtkWidget* window) {

	gtk_main_quit(); // 창이 파괴되면 메인 루프를 죽입니다.

}



static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window) {

	gtk_widget_destroy(window); // 자바스크립트로 창 닫기를 요청하면 창을 죽입니다. 그러면 위에 콜백도 함께 실행될겁니다.

	return TRUE;

}



int main(int argc, char** argv) {

	gtk_init(&argc, &argv);



	GtkWidget* mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_default_size(GTK_WINDOW(mainWindow), 800, 600);



// 웹뷰 위젯을 하나 만들어서

	WebKitWebView* webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

	gtk_container_add(GTK_CONTAINER(mainWindow), GTK_WIDGET(webView)); // 컨테이너에 붙힙니다.



// 콜백들을 등록해주고요.

	g_signal_connect(mainWindow, "destroy", G_CALLBACK(destroyWindowCb), NULL);

	g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), mainWindow);



// 웹페이지를 로딩시킵니다.

	webkit_web_view_load_uri(webView, "http://codeview.github.io/runblox-private-pro-site");

	gtk_widget_grab_focus(GTK_WIDGET(webView));

	gtk_widget_show_all(mainWindow);



	gtk_main();

}