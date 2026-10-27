# Project Best Practices and Standards/Methods

## Guiding Values and Principles

---

## Use of Artificial Intelligence, LLMs, and Upfront Communication

---

## Pull/Merge Requests

### Pull/Merge requests from *internal branches or forks*:

- Should be made sparingly, reserved for large milestone completions, or meaningful changes from development to production.
- Named with Version/Number, most meaningful or general change(s), and origin: i. e. "#4; Added new math directory and implemented window handling; origin/dev"
  - *Each 'section' seperated by semicolon(;), use full path names for origin, number should be total pull request number for that branch.*

### Pull/Merge requests from *others or outside forks*:

- Generally disallowed, as this is a personal and educational project, there is no benefit and no need for others to make contributions.
  - *Exceptions include: professor or classmates making small suggestions or changes, co-work or mentorship on another's device/account, properly credited external sources/repos.*

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



---

## Naming Conventions
- **Variables:** lowerCamelCase (myVar, newInt, etc)
- **Functions:** UpperCamelCase (AddNumbers(), DeleteName(), etc)

---

## Crediting and Referencing
