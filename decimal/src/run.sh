#!/bin/bash

docker build -t image_for_review:1 -f Dockerfile .
docker run -it --rm image_for_review:1 bash
