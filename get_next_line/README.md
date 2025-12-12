*This project has been created as part of the 42 curriculum by mande-so.*

# get_next_line

## Description

This function reads a file line by line. Every time I call it, it gives me the next line including the newline at the end. When there's nothing left to read, it returns NULL.

I used a static buffer to remember where I stopped reading. This way the function can handle any buffer size efficiently because it saves leftover data for the next call.

For the bonus I added support for multiple files at once by using an array of buffers - each file gets its own buffer.

## Instructions

### How to compile

Mandatory:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

Bonus:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c

### How to use

Mandatory:

```c
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```


Bonus (multiple files):

```c
int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
	line = get_next_line(fd1);
	printf("File1: %s", line);
	free(line);
	line = get_next_line(fd2);
	printf("File2: %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("File1: %s", line);
	free(line);
	close(fd1);
	close(fd2);
	return (0);
}
```

## Algorithm Explanation

### Mandatory version

My approach was pretty simple - keep a static buffer to save leftover data between function calls, and build the line piece by piece until I find a newline.

How it works:

1. Static buffer
	- I used static so the buffer doesn't disappear after the function ends
	- It saves any leftover data after I extract a line

2. Validation at the start
	- First I check if the fd is valid and if BUFFER_SIZE makes sense
	- If something's wrong, I return NULL

3. The main loop
	- If the buffer is empty, I read more data from the file
	- If it's still empty after reading, that means EOF so I stop
	- I add the buffer content to the line I'm building
	- If malloc fails, I clean up and return NULL
	- When I find a newline, I save the leftover data and return the line
	- If no newline yet, I clear the buffer and read more

4. At the end
	- If there's no line or it's empty, I return NULL
	- Otherwise I return whatever's left (for files without a final newline)

Helper functions:
- ft_fillbuf: reads from the file into the buffer
- ft_strjoin: joins two strings, stops at newline, frees the old one
- ft_findnl: checks if there's a newline in the buffer
- ft_shiftbuf: moves leftover data to the start for the next call

Example:
File has "Hello\nWorld\n", buffer size is 10

Call 1: read "Hello\nWorl", return "Hello\n", keep "World\n" in buffer
Call 2: already have "World\n" in buffer, return "World\n"
Call 3: buffer empty, read returns 0 (end of file), return NULL

### Bonus version

The bonus works exactly the same way, but uses an array of buffers instead of just one:

static char buffer[OPEN_MAX][BUFFER_SIZE + 1];

Each file descriptor gets its own buffer at buffer[fd], so I can read from multiple files at the same time without mixing up their data.

Why OPEN_MAX is limited to 64:
If OPEN_MAX was 1024 and someone used a huge BUFFER_SIZE, it would try to allocate gigabytes on the stack and crash. So I limited it to 64 which is plenty for most cases.

## Resources

- man read
- man open
- Google and Stack Overflow when I got stuck
- GitHub Copilot for help with debugging

I used Copilot to understand some errors and get explanations when I didn't know what was wrong. But I wrote all the code myself and made sure I understood what everything does before using it.
