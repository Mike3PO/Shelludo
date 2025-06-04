# Shelludo

Shelludo is a shell programmed in C for UMD students made by a UMD student that is customizable and allows for basic queries on testudo.

## Installation

You can clone the repository and then build it on your machine. You will need gcc, make, and a Unix like terminal.

```bash
git clone https://github.com/Mike3PO/Shelludo.git
cd Shelludo
make shelludo
```
You can then run it with

```bash
./shelludo
```

## Usage

The world's your oyster! You can change the foreground and backround colors, navigate your directories as usual, use simple piping and commands supported by Unix, and more! For a full list of what Shelludo is capable of use

```bash
help
```
Specifically you can view all departments at UMD and courses in those departments. A common series of commands would look something like this.

```bash
departments
departments -c # Outputs list of departments such as CMSC, MATH
courses CMSC # Prints out all the courses in CMSC
```
## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[Apache 2.0](https://choosealicense.com/licenses/apache-2.0/)