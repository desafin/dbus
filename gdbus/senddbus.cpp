#include <gio/gio.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    GDBusConnection *connection;
    GError *error = NULL;
    GVariant *result;

    // D-Bus 시스템 버스에 연결
    connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    if (connection == NULL) {
        g_printerr("Error connecting to D-Bus: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // D-Bus 메서드 호출
    result = g_dbus_connection_call_sync(connection,
                                         "com.example.Service",  // D-Bus 서비스 이름
                                         "/com/example/Object",  // 객체 경로
                                         "com.example.Interface",// 인터페이스 이름
                                         "MethodName",           // 호출할 메서드 이름
                                         NULL,                   // 매개변수 없음
                                         NULL,                   // 응답 타입
                                         G_DBUS_CALL_FLAGS_NONE,
                                         -1,                     // 타임아웃 없음
                                         NULL,
                                         &error);

    // 결과 처리
    if (result == NULL) {
        g_printerr("Error calling method: %s\n", error->message);
        g_clear_error(&error);
    } else {
        // 결과 사용 (예: 문자열 출력)
        gchar *response;
        g_variant_get(result, "(s)", &response);
        g_print("Method response: %s\n", response);
        g_free(response);
        g_variant_unref(result);
    }

    // 연결 닫기
    g_object_unref(connection);
    return 0;
}
