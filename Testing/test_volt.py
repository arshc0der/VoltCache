import socket
import time
import json

class VoltClient:
    def __init__(self, host="127.0.0.1", port=8080):
        self.host = host
        self.port = port

    def execute(self, command):
        """Helper to send a command and get a response."""
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.settimeout(2) # Don't hang forever if server is down
                s.connect((self.host, self.port))
                s.sendall(command.encode('utf-8'))
                data = s.recv(1024)
                return data.decode('utf-8').strip()
        except Exception as e:
            return f"CONNECTION_ERROR: {e}"

def run_mnc_test_suite():
    client = VoltClient()
    print("🚀 Starting VoltCache Professional Test Suite\n" + "="*40)

    # 1. Simple String Test
    print("[1] Testing Basic SET/GET...")
    client.execute("SET developer Arsh")
    resp = client.execute("GET developer")
    print(f"    Response: {resp} (Expected: Arsh)")

    # 2. JSON/Structured Data Test
    print("\n[2] Testing JSON Structured Data...")
    user_data = {"id": 1, "status": "active", "points": 500}
    client.execute(f"SET user:1 {json.dumps(user_data)}")
    resp = client.execute("GET user:1")
    print(f"    Retrieved JSON: {resp}")

    # 3. Bulk Data Stress Test
    print("\n[3] Testing Bulk Data (100 keys)...")
    start_time = time.time()
    for i in range(100):
        client.execute(f"SET key_{i} value_{i}")
    duration = time.time() - start_time
    print(f"    Finished 100 operations in {duration:.4f} seconds")

    # 4. Persistence Verification
    print("\n[4] Data Persistence Check...")
    print("    Check your 'data/volt.log' file now.")
    print("    You should see all 'SET' commands recorded there.")
    
    print("\n" + "="*40 + "\n✅ Test Suite Complete!")

if __name__ == "__main__":
    run_mnc_test_suite()