#ifndef BTIMETABLE_CLIENTAPI_H
#define BTIMETABLE_CLIENTAPI_H

#include "Entities.h"

namespace db {
class ClientAPI {
public:
    static std::string createClient(const std::string &phoneNumber,
                                    const std::string &password,
                                    const std::string &fullName,
                                    const std::string &email);

    static std::string authorizeClient(const std::string &phoneNumber,
                                       const std::string &password);

    static std::vector<long long> listCompanies();

    static std::vector<long long> listOrders(long long companyId,
                                             long long employeeId,
                                             Order::statusEnum status,
                                             long long leastTimeStart = 0,
                                             long long leastDuration = 0,
                                             sortParam sortBy = byId,
                                             bool reversed = true);

    static std::vector<long long> listVacantOrdersOfCompany(
        long long companyId);

    static std::vector<long long> listEmployeesOfCompany(long long companyId);

    static void bookOrder(const std::string &token, long long orderId);

    static void cancelOrder(const std::string &token, long long orderId);

    static void rateOrder(const std::string &token,
                          long long orderId,
                          int rating);

    static Client getClient(const std::string &token);

    static Order getOrderById(const std::string &token, long long orderId);

    static Employee getEmployeeById(long long employeeId);

    static Company getCompanyById(long long companyId);

    static void changeClientFullName(const std::string &token,
                                     std::string fullName);

    static void changeClientEmail(const std::string &token, std::string email);

    static std::vector<long long> listOrdersOfClient(const std::string &token);

    static std::vector<long long> listVacantOrdersOfEmployee(
        long long employeeId);
};
}  // namespace db

#endif  // BTIMETABLE_CLIENTAPI_H
