# CMSC32002_secure_code_gen
Secure code generation project for CMSC 32002, Topics In Software Engineering: Machine Learning for Programming

Henry, Isha, and Justin

## Usage
### Setup

1. Create a virtual environment (only needed once)
```
python -m venv venv
```
2. Activate the virtual environment 
```
source venv/bin/activate
```
3. Install the requirements (only needed once)
```
pip install -r requirements.txt
```

### CWEval
The main part of this code involves using CWEval. Please follow these instructions, largely from `https://github.com/Co1lin/CWEval`:
1. Pull the docker image (only needed once)
```bash
docker pull --platform=linux/amd64 co1lin/cweval
```  
2. Run the docker image
```bash
docker run --platform=linux/amd64 --name cweval --rm -it --net host co1lin/cweval zsh
```
3. In another terminal, copy the `cwe_test_gen.py` script to the container
```bash
docker cp cwe_test_gen.py cweval:/home/ubuntu/CWEval
```
4. In the docker container, set up the environment:
```bash
source .env
export OPENAI_API_KEY=<your key here>
export GOARCH=amd64
export GOOS=linux
```
5. Run the script
```bash
python cwe_test_gen.py "<lang>" "<model_name>"
```
6. Save the csv results to a local file and save all the evaluation code and history
```bash
docker cp cweval:/home/ubuntu/CWEval/results .
docker cp cweval:/home/ubuntu/CWEval/evals .
```
7. Run the stats notebook locally in `stat_evaluation.ipynb`