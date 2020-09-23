FROM python:3.8-slim as RUNNING

RUN apt-get update \
    && apt install -y g++ build-essential

COPY requirements.txt /
COPY Makefile /app/
COPY accuracy/ /app/accuracy/
COPY plotting/ /app/plotting/
COPY video/ /app/video/
COPY src/ /app/src/

RUN cd app && make

RUN pip install -r requirements.txt

CMD [ "python", "app/plotting/plot.py" ]
