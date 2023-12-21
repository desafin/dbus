#include <gio/gio.h> // GDBus를 사용하기 위한 헤더 파일
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    GDBusConnection *connection; // GDBusConnection 객체 선언
    GError *error = NULL;        // GError 객체 선언
    GVariant *result;            // 결과를 저장할 GVariant 객체 선언

    // D-Bus 시스템 버스에 연결
    // G_BUS_TYPE_SYSTEM은 시스템 버스를 나타냄
    connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    if (connection == NULL) {
        // 연결 실패 시 에러 메시지 출력 및 프로그램 종료
        g_printerr("Error connecting to D-Bus: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // D-Bus 메서드 호출
    // g_dbus_connection_call_sync 함수를 사용하여 동기적으로 메서드 호출
    result = g_dbus_connection_call_sync(connection,
                                         "com.example.Service",  // D-Bus 서비스 이름
                                         "/com/example/Object",  // 객체 경로
                                         "com.example.Interface",// 인터페이스 이름
                                         "MethodName",           // 호출할 메서드 이름
                                         NULL,                   // 매개변수 없음
                                         NULL,                   // 응답 타입
                                         G_DBUS_CALL_FLAGS_NONE, // 호출 플래그
                                         -1,                     // 타임아웃 없음
                                         NULL,                   // 취소 가능한 객체
                                         &error);                // 에러 객체

    // 결과 처리
    if (result == NULL) {
        // 메서드 호출 실패 시 에러 메시지 출력
        g_printerr("Error calling method: %s\n", error->message);
        g_clear_error(&error);
    } else {
        // 메서드 호출 성공 시 결과 처리
        gchar *response;
        g_variant_get(result, "(s)", &response); // 결과 파싱 (문자열)
        g_print("Method response: %s\n", response);
        g_free(response);                      // 메모리 해제
        g_variant_unref(result);               // GVariant 객체 해제
    }

    // 연결 닫기
    g_object_unref(connection); // GDBusConnection 객체 해제
    return 0;
}
s