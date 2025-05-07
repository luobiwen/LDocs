#include"myDSManager.h"
void myDSManager::handleResponse(QNetworkReply *reply) {
    return;
}

void myDSManager::sendRequest(const QString &prompt){
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    QByteArray a="";
    manager->post(request,a);
}
