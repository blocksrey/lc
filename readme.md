# lc
lc (list contents) is a command-line utility aimed at addressing the limitations and conventions of ls, the standard file listing command in Unix-like operating systems. It offers an improved approach to listing files and directories in a more straightforward and intuitive manner, particularly when dealing with hidden files (dotfiles).

## Why lc?
### The shortcomings of ls
ls has long been the go-to command for listing files in a directory. However, it comes with some limitations and conventions that can be cumbersome:

**Hidden Files**: ls hides files and directories whose names start with a dot (.) by default. This can lead to confusion and inconvenience when trying to view or manipulate these hidden resources.

**Non-Intuitive Syntax**: There's no simple way to list only dotfiles or non-dotfiles using ls. You need to resort to complex regex or globbing patterns, making it less user-friendly.

**Limited Customization**: Customizing the output of ls requires remembering various flags, which can be confusing for users, especially those new to the command.

## *The Solution*: lc
lc addresses these issues and provides a more user-friendly and intuitive way to list files and directories:

**Show Hidden Files**: lc displays hidden files (dotfiles) by default. This eliminates the need to use complex patterns to view them.

**Simple Syntax**: lc introduces a straightforward syntax for listing dotfiles (.*) or non-dotfiles (!.*). This makes it easy to filter and view specific types of files.

**Customizable Output**: lc allows users to customize the output format using simple flags, making it more flexible and user-friendly.

## Reasons that dotfiles shouldn't be hidden by default, but rather presented differently in file listings:
1. Transparency and Discoverability: Hidden dotfiles are not readily discoverable by users who are not familiar with the convention. When users are unaware of their existence, they may miss out on crucial configuration files or important data stored in these files. By making dotfiles visible by default, users can more easily understand and access them.
2. Consistency: Treating all files and directories consistently, regardless of whether they are considered configuration or data, simplifies the user experience. Users can apply the same set of actions (e.g., copying, moving, deleting) to all files without having to remember special flags or patterns for hidden files.
3. Simplifies Scripting and Automation: When dealing with automation, scripting, or creating tools that interact with files and directories, it's more straightforward to process all files uniformly. Having dotfiles hidden by default introduces complexity, as developers need to account for this hidden status in their code.
4. Avoiding Obscured Data Loss: Hidden dotfiles are often ignored when users perform actions like deleting files. This can lead to unintentional data loss if users are not aware of the existence of these files. By making them visible, users are less likely to overlook them during file management tasks.
5. User Choice and Flexibility: Hiding dotfiles by default restricts user choice and flexibility. Different users have different preferences, and some may prefer to keep dotfiles visible at all times for ease of access and management. Providing visibility as the default option empowers users to make their own decisions about how they want to interact with their files.
6. Reducing Cognitive Load: For users new to Unix-like systems, the concept of hidden files can be confusing and add unnecessary cognitive load. Having all files visible simplifies the initial learning curve, making the system more approachable.
7. Better Integration with Graphical File Managers: Many graphical file managers, such as those used in modern desktop environments, hide dotfiles by default. This can create an inconsistency between command-line and graphical file management. By making dotfiles visible by default, the two interfaces can align more closely, improving the overall user experience.