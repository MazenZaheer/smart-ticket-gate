# Smart Ticket Gate Simulation

A small C++ simulation of a smart-gate ticket validation system, built during
the **"AI in Public Transport and Smart Ticketing Systems"** course by
**NSS IT Solution Sdn Bhd** (March 2026).

The program models a simplified ticket gate: a rider enters a ticket code,
and the system runs it through three checks before granting or denying
access — mimicking how a real smart-ticketing gate might combine an API
check, a duplicate-use check, and a fare/zone validity check.

## How it works

1. **API verification (mocked)** — `verifyTicketWithAPI()` stands in for a
   call to a real ticketing backend. In this simulation it always returns
   `true`; it's a hook for where a live API call would go.
2. **Duplicate-use check** — previously used ticket codes are persisted to
   `used_tickets.txt` and reloaded on every run, so a ticket can't be reused
   across sessions (simulates anti-fraud / single-use enforcement).
3. **Range validation** — the numeric portion of the ticket code is
   extracted and must fall between 31–40 (a stand-in for a valid
   fare/zone/batch range for this course exercise).
4. **Result** — access is granted or denied, and valid tickets are logged.

## Build & run

```bash
g++ -std=c++17 -o smart_ticket_gate main.cpp
./smart_ticket_gate
```

Example:

```
Enter ticket number: TKT035
Access Granted: Ticket is valid. Gate opened.
```

Running it again with the same code:

```
Enter ticket number: TKT035
Access Denied: Ticket has already been used.
```

## Project structure

```
.
├── main.cpp          # Core simulation logic
├── used_tickets.txt  # Auto-generated log of used tickets (gitignored)
└── README.md
```

## Notes / limitations

This was a teaching exercise focused on core logic (file I/O, string
parsing, basic validation flow) rather than a production ticketing system.
Known simplifications worth being upfront about:

- `verifyTicketWithAPI()` is a stub — no real network call is made.
- The valid range (31–40) is hardcoded for the exercise rather than
  configurable or fare-based.
- No encryption, authentication, or concurrency handling — a real gate
  system would need all three.

## Course context

Built as part of a hands-on C++ module in a broader course on AI
applications in public transport and smart ticketing, covering concepts
like automated fare validation, fraud prevention (duplicate-use checks),
and API-based verification pipelines.
