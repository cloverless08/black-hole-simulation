# Project Best Practices and Standards/Methods


## Guiding Values and Principles



---

## Use of Artificial Intelligence, LLMs, and Upfront Communication

AI use will be clearly and proactively described and disclaimed in all necessary documents (most specifically, the README.md).

As is standard convention in my projects, and to uphold my education
and academic honesty, *no generative AI tools (such as ChatGPT or Claude Code)
were used to write, generate, or create any code or other submitted project content.*

***Any use of Artificial Intelligence (LLMs, Generative AI, Vibe-Coding tools) MUST be clearly stated and listed
in their entirety, no matter what.***

Some Examples of what should be listed include:
- Resource compilation.
- Idea generation or brainstorming.
- **Any generated content or files**
- Indexing or refactoring

---

## Pull/Merge Requests

### Pull/Merge requests from *internal branches or forks*:

*assuming that "internal branches" are made and contributed to by the original author only*

- Should be made sparingly, reserved for large milestone completions, or meaningful changes from development to production.
- Named with Version/Number, most meaningful or general change(s), and origin: i. e. "#4; Added new math directory and implemented window handling; origin/dev"
  - *Each 'section' seperated by semicolon(;), use full path names for origin, number should be total pull request number for that branch.*

### Pull/Merge requests from *others or outside forks*:

- Generally disallowed, as this is a personal and educational project, there is no benefit and no need for others to make contributions.
  - *Exceptions include: professor or classmates making small suggestions or changes,
  co-work or mentorship on another's device/account, 
  properly credited external sources/repos (where applicable).*

---

## Main Branch and Other Branching Conventions

A typical branch structure might look like:

~~~
origin/
|- main/
| |-<working project files>
|- dev/
| |-<project files under development>
| |-<new, incomplete features>
~~~

The **main** branch is considered the production environment. Any files staged in this branch should
reflect a finished, working snapshot of code that can be cloned and demonstrated.

The **dev** branch is for active development (obviously lol). Pretty much free-reign for unfinished and current-working
files. Nothing here *has* to be finished and should be where most commits are pushed before staging to main.

---

## File Structure


---

## Naming Conventions
- **Variables:** lowerCamelCase (myVar, newInt, etc)
- **Functions:** UpperCamelCase (AddNumbers(), DeleteName(), etc)
- **Namespaces:** All lower case (test, algorithm, etc)
- **Classes:** While these are usually one word, use UpperCamelCase like functions, no need to make
it complicated
- **Files:** All lower case, never use spaces.
Always use single words when possible, but separate with underscores when not.
Use .h for header files (as apposed to .hpp)

---

## Crediting and Referencing
