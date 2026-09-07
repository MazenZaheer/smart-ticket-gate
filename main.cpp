/*
 * Smart Ticket Gate — AI in Public Transport & Smart Ticketing Systems
 * Course project | NSS IT Solution Sdn Bhd | March 2026
 *
 * Simulates a smart-gate ticket validation flow:
 *   1. Check ticket against a (mocked) external verification API
 *   2. Reject already-used tickets (persisted to disk)
 *   3. Validate the ticket number falls within an accepted range
 *   4. Grant/deny access and log used tickets for future runs
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <cctype>

using namespace std;

// Load previously used ticket numbers from disk so they aren't reused
// across multiple runs of the program.
set<string> loadUsedTickets(const string& filename) {
    set<string> usedTickets;
    ifstream inFile(filename);
    string ticket;
    while (getline(inFile, ticket)) {
        if (!ticket.empty()) {
            usedTickets.insert(ticket);
        }
    }
    inFile.close();
    return usedTickets;
}

// Append a newly validated ticket to the persistent used-tickets log.
void saveUsedTicket(const string& filename, const string& ticketNo) {
    ofstream outFile(filename, ios::app);
    outFile << ticketNo << endl;
    outFile.close();
}

// Extract the numeric portion of a ticket code (e.g. "TKT035" -> 35).
int extractTicketNumber(const string& ticketNo) {
    string digits = "";
    for (char ch : ticketNo) {
        if (isdigit(static_cast<unsigned char>(ch))) {
            digits += ch;
        }
    }
    if (digits.empty()) {
        return -1;
    }
    return stoi(digits);
}

// Placeholder for a real external verification call (e.g. a backend
// ticketing API). Always returns true in this simulation.
bool verifyTicketWithAPI(const string& ticketNo) {
    return true;
}

int main() {
    const string usedTicketsFile = "used_tickets.txt";
    set<string> usedTickets = loadUsedTickets(usedTicketsFile);

    string ticketNo;
    cout << "Enter ticket number: ";
    cin >> ticketNo;

    bool apiValid = verifyTicketWithAPI(ticketNo);
    if (!apiValid) {
        cout << "Access Denied: API says ticket is invalid." << endl;
        return 0;
    }

    if (usedTickets.find(ticketNo) != usedTickets.end()) {
        cout << "Access Denied: Ticket has already been used." << endl;
        return 0;
    }

    int ticketNumber = extractTicketNumber(ticketNo);
    if (ticketNumber < 31 || ticketNumber > 40) {
        cout << "Access Denied: Ticket number is not in valid range." << endl;
        return 0;
    }

    cout << "Access Granted: Ticket is valid. Gate opened." << endl;
    usedTickets.insert(ticketNo);
    saveUsedTicket(usedTicketsFile, ticketNo);

    return 0;
}
