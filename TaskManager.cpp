#include "TaskManager.h"
using std::string;
using namespace std;
#include <stdexcept>



// Default constructor
TaskManager::TaskManager()
        : m_employeeCount(0), m_nextTaskId(0)
{
    // Initialize all employee pointers to nullptr
    for (int i = 0; i < MAX_PERSONS; ++i) {
        m_employees[i] = nullptr;
    }
}


TaskManager::~TaskManager() {
    for (int i = 0; i < m_employeeCount; ++i) {
        delete m_employees[i];
    }
}

void TaskManager::assignTask(const string& employeeName, const Task& task) {
    // Try to find the employee by name
    Person* targetEmployee = nullptr;
    for (int i = 0; i < m_employeeCount; ++i) {
        if (m_employees[i]->getName() == employeeName) {
            targetEmployee = m_employees[i];
            break;
        }
    }

    // If the employee is not found and the system is full
    if (targetEmployee == nullptr) {
        if (m_employeeCount >= MAX_PERSONS) {
            throw std::runtime_error("Cannot add more employees, system is full.");
        }

        // If the employee is not found, we add them to the system
        targetEmployee = new Person(employeeName);  // Create a new Person object
        m_employees[m_employeeCount++] = targetEmployee;  // Add the employee to the array and increment count
    }

    // Assign the task with the next available ID
    Task newTask = task;
    newTask.setId(m_nextTaskId);  // Set the ID of the task

    // Add the task to the employee's task list
    targetEmployee->assignTask(newTask);

    // Increment the task ID for the next task
    m_nextTaskId++;
}

void TaskManager::completeTask(const string& employeeName) {
    // Try to find the employee by name
    Person* targetEmployee = nullptr;
    for (int i = 0; i < m_employeeCount; ++i) {
        if (m_employees[i]->getName() == employeeName) {
            targetEmployee = m_employees[i];
            break;
        }
    }

    // If the employee is found, remove the highest priority task
    if (targetEmployee != nullptr) {
        // Complete the task by removing the highest priority task (first task in list)
        targetEmployee->completeTask();
    }
    // If the employee is not found, do nothing (as per the requirement)
}


void TaskManager::bumpPriorityByType(TaskType type, int priorityIncrease) {
    // If the number is negative, do nothing
    if (priorityIncrease < 0) {
        return;
    }
    for (int i = 0; i < m_employeeCount; ++i) {
        Person* person = m_employees[i];
        SortedList<Task> updatedTasks;

        for (auto iter = person->getTasks().begin(); iter != person->getTasks().end(); ++iter) {
            Task task = *iter;
            if (task.getType() == type) {
                Task updatedTask(task.getPriority() + priorityIncrease, task.getType(), task.getDescription());
                updatedTask.setId(task.getId());
                updatedTasks.insert(updatedTask);
            } else {
                updatedTasks.insert(task);
            }
        }

        person->setTasks(updatedTasks);
    }
}

void TaskManager::printAllEmployees() const {
    // Iterate over all employees
    for (int i = 0; i < m_employeeCount; ++i) {
        // Print each employee (using the overloaded << operator)
        std::cout << *m_employees[i] << std::endl;
    }
}



void TaskManager::printAllTasks() const {
    Task* allTasks[100];
    int taskNum = 0;

    for (int i = 0; i < m_employeeCount; ++i) {
        const SortedList<Task>& tasks = m_employees[i]->getTasks();
        for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
                allTasks[taskNum] = const_cast<Task*>(&(*iter));
            taskNum++;
        }
    }
    taskNum--;
    for (int k = 0; k < taskNum; ++k) {
        for (int i = 0; i < taskNum - k; ++i) {
            if (allTasks[i]->getPriority() < allTasks[i + 1]->getPriority()) {
                Task* task_temp = allTasks[i];
                allTasks[i] = allTasks[i + 1];
                allTasks[i + 1] = task_temp;
            }
        }
    }

    for (int i = 0; i <= taskNum; ++i) {
        std::cout << *(allTasks[i]) << std::endl;
    }
}


void TaskManager::printTasksByType(TaskType type) const {
    Task* taskByType[100];
    int taskNum = 0;

    for (int i = 0; i < m_employeeCount; ++i) {
        const SortedList<Task>& tasks = m_employees[i]->getTasks();
        for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
            const Task& temp = *iter;
            if (temp.getType() == type) {
                taskByType[taskNum] = new Task(temp);
                taskNum++;
            }
        }
    }
    taskNum--;
    for (int i = 0; i < taskNum; ++i) {
        for (int j = 0; j < taskNum - i; ++j) {
            if (taskByType[j]->getPriority() < taskByType[j + 1]->getPriority()) {
                Task* task_temp = taskByType[j];
                taskByType[j] = taskByType[j + 1];
                taskByType[j + 1] = task_temp;
            }
        }
    }

    for (int i = 0; i <= taskNum; ++i) {
        cout << *taskByType[i] << endl;
        delete taskByType[i];
    }
}