gitlog=`echo "Build CI completed: " $(git log -1 --pretty=format:"%h - %an, %ar : %s")`
echo $gitlog

curl -X POST \
   -H 'Content-Type: application/json' \
   -d '{"chat_id": "-1001419585850", "text": "'"$gitlog"'", "disable_notification": true}' \
   https://api.telegram.org/bot348763180:AAHe05jJ_rtHTcC0vw79qwGcA-ByHNXsIvM/sendMessage
