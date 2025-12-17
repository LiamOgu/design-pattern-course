#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

class Sql {
public:
  std::vector<std::string> colonnes;
  std::string table;
  std::vector<std::string> condition;
  int limit = 0;

  void afficherRequete() const {
    std::cout << "SELECT ";
    for (size_t i = 0; i < colonnes.size(); ++i) {
      std::cout << colonnes[i];
      if (i + 1 < colonnes.size())
        std::cout << ", ";
    }
    std::cout << " FROM " << table << std::endl;

    if (!condition.empty()) {
      for (size_t i = 0; i < condition.size(); i++) {
        if (i == 0) {
          std::cout << "WHERE " << condition[i] << std::endl;
        } else {
          std::cout << "AND " << condition[i] << std::endl;
        }
      }
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
    sql.table = fromTable;
    sql.colonnes = {"*"};
    sql.condition = {""};
    sql.limit = 0;
  }

  SqlBuilder &from(const std::string &fromQuery) {
    sql.table = fromQuery;
    return *this;
  }

  SqlBuilder &select(const std::vector<std::string> &selectColumns) {
    sql.colonnes = selectColumns;
    return *this;
  }

  SqlBuilder &where(const std::vector<std::string> &whereCondition) {
    sql.condition = whereCondition;
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

  SqlBuilder builder2("produit");

  Sql req1 = builder.select({"nom", "email"})
                 .where({"actif = 1", "age >= 18"})
                 .limit(5)
                 .build();

  req1.afficherRequete();

  Sql req2 = builder2.from("commande").where({"montant > 100"}).build();

  req2.afficherRequete();
}
