#include <iostream>
#include <string>
#include <vector>

class Sql {
public:
  std::vector<std::string> select;
  std::string from;
  std::string where;
  int limit = 0;

  void afficherRequete() const {
    std::cout << "SELECT ";
    for (size_t i = 0; i < select.size(); ++i) {
      std::cout << select[i];
      if (i + 1 < select.size())
        std::cout << ", ";
    }
    std::cout << " FROM " << from << std::endl;

    if (!where.empty()) {
      std::cout << "WHERE " << where << std::endl;
    }
    if (limit > 0) {
      std::cout << "LIMIT " << limit << std::endl;
    }
  }
};

class SqlBuilder {
private:
  Sql sql;

  SqlBuilder() = delete;
  SqlBuilder(const SqlBuilder &) = delete;
  void operator=(const SqlBuilder &) = delete;

public:
  SqlBuilder(const std::string &fromTable) {
    sql.from = fromTable;
    sql.select = {"*"};
    sql.where = "";
    sql.limit = 0;
  }

  SqlBuilder &from(const std::string &fromQuery) {
    sql.from = fromQuery;
    return *this;
  }

  SqlBuilder &select(const std::vector<std::string> &selectColumns) {
    sql.select = selectColumns;
    return *this;
  }

  SqlBuilder &where(const std::string &whereCondition) {
    sql.where = whereCondition;
    return *this;
  }

  SqlBuilder &limit(int limitNumber) {
    sql.limit = limitNumber;
    return *this;
  }

  Sql build() { return sql; }
};

int main() {
  SqlBuilder builder("client");

  Sql req1 =
      builder.select({"nom", "email"}).where("actif = 1").limit(5).build();

  req1.afficherRequete();
}
