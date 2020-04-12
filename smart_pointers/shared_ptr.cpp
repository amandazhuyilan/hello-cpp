#include <iostream>
#include <memory>

class Project {
};

class Employee {
	std::shared_ptr<Project> m_project;

public:
	void SetProject(std::shared_ptr<Project> project) {
		m_project = project;
	}
	
	std::shared_ptr<Project> GetProject() {
		return m_project;
	}
	
};

std::shared_ptr<Employee> AssignProject() {
	std::shared_ptr<Project> shared_project(new Project);
	Employee *e1 = new Employee;
	(*e1).SetProject(shared_project);
	return std::shared_ptr<Employee> (e1);
}

int main() {
	auto sp = AssignProject();
	return 0;
}
