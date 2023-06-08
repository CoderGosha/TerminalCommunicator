# Terminal Communicator 
Распределенная система запросов, клиенты в том числе для роутеров

### Run python client with docker 

```
sudo docker build -t cg_communicator . -f Clients/Python.Client/Dockerfile

sudo docker run -d \
-e API_KEY='' \
-e API_URL='' \
-e NAME='CG.-.Python' \ 
--name cg_communicator cg_communicator

```