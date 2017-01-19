import argparse
import re

def get_args():
    # You can change the default search term here if you would like
    newTerm = ""
    # newTerm = "Android"
    file = "cs-access.log"

    parser = argparse.ArgumentParser()

    configuration = parser.add_argument_group("Configuration")
    # This will not actually be used since Linux and android with be hard coded
    configuration.add_argument("-t", "--term", dest="search_term",
        default=newTerm, help="Term to find within the file")
    configuration.add_argument("-f", "--filename", dest="filename",
        default=file, help="File to search")

    return parser.parse_args()


def print_ips_and_get_requests(regex_term, file):
    # Setup regex
    search_term_regex = "\([^\)]*("+regex_term+")[^\)]*\)"
    ip_address_regex = ("(^((25[0-5])?(2[0-4][0-9])?(1?[0-9]?[0-9])?)\."
        "((25[0-5])?(2[0-4][0-9])?(1?[0-9]?[0-9])?)\.((25[0-5])?"
        "(2[0-4][0-9])?(1?[0-9]?[0-9])?)\.((25[0-5])?(2[0-4][0-9])?"
        "(1?[0-9]?[0-9])?))")
    get_regex = "(GET[^\"]+)\""

    p = re.compile(ip_address_regex+".*"+get_regex+".*"+search_term_regex)

    ips = []
    get_requests = []

    try:
        lines = [line.rstrip('\n') for line in open(file)]
        for line in lines:
            m = p.search(line)
            if m:
                if m.group(1) not in ips:
                    ips.append(m.group(1))
                if m.group(18) not in get_requests:
                    get_requests.append(m.group(18))

    except IOError as e:
        print("Could not locate file %s", args.filename)

    ips.sort()
    get_requests.sort()

    print("\n"+regex_term+" ip addresses and GET Requests.")

    for ip in ips:
        print ip

    for get_request in get_requests:
        print get_request

if __name__ == "__main__":
    args = get_args()

    print_ips_and_get_requests("Linux", args.filename)

    print_ips_and_get_requests("Android", args.filename)

    if args.search_term is not "":
        print_ips_and_get_requests(args.search_term, args.filename)
