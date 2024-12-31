/* XXX DOES NOT USE BUILT-IN DETECTION FUNCTION XXX
alert tcp $EXTERNAL_NET $HTTP_PORTS -> $HOME_NET any (msg:"WEB-CLIENT Microsoft Office Excel BRAI record remote code execution attempt"; flowbits:isset,file.xls; flow:to_client,established; content:"|1e 04|"; content:"|51 10|"; metadata:policy balanced-ips drop, policy security-ips drop, service http; reference:cve,2009-0549; reference:url,technet.microsoft.com/en-us/security/bulletin/MS09-021; classtype:attempted-user; sid:15519; rev:1;)
*/
/*
 * Use at your own risk.
 *
 * Copyright (C) 2005-2008 Sourcefire, Inc.
 * 
 * This file is autogenerated via rules2c, by Brian Caswell <bmc@sourcefire.com>
 */


#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

#include "so-util.h"

//#define DEBUG 1
#ifdef DEBUG
#define DEBUG_WRAP(code) code
#else
#define DEBUG_WRAP(code)
#endif

/* declare detection functions */
int rule15519eval(void *p);

/* declare rule data structures */
/* precompile the stuff that needs pre-compiled */
/* flowbits:isset "file.xls"; */
static FlowBitsInfo rule15519flowbits0 =
{
    "file.xls",
    FLOWBIT_ISSET,
    0,
};

static RuleOption rule15519option0 =
{
    OPTION_TYPE_FLOWBIT,
    {
        &rule15519flowbits0
    }
};
/* flow:established, to_client; */
static FlowFlags rule15519flow1 = 
{
    FLOW_ESTABLISHED|FLOW_TO_CLIENT
};

static RuleOption rule15519option1 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule15519flow1
    }
};
// content:"|1E 04|", depth 0; 
static ContentInfo rule15519content2 = 
{
    (uint8_t *) "|1E 04|", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_RELATIVE|CONTENT_BUF_NORMALIZED|CONTENT_FAST_PATTERN, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15519option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15519content2
    }
};
// content:"Q|10|", depth 0; 
static ContentInfo rule15519content3 = 
{
    (uint8_t *) "Q|10|", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_RELATIVE|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15519option3 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15519content3
    }
};

/* references for sid 15519 */
/* reference: cve "2009-0549"; */
static RuleReference rule15519ref1 = 
{
    "cve", /* type */
    "2009-0549" /* value */
};

/* reference: url "technet.microsoft.com/en-us/security/bulletin/MS09-021"; */
static RuleReference rule15519ref2 = 
{
    "url", /* type */
    "technet.microsoft.com/en-us/security/bulletin/MS09-021" /* value */
};

static RuleReference *rule15519refs[] =
{
    &rule15519ref1,
    &rule15519ref2,
    NULL
};
/* metadata for sid 15519 */
/* metadata:service http, policy balanced-ips drop, policy security-ips drop; */
static RuleMetaData rule15519service1 = 
{
    "service http"
};


// pmullen commenting out the balanced-ips policy for fear of false positives
//static RuleMetaData rule15519policy1 = 
//{
//    "policy balanced-ips drop"
//};

//static RuleMetaData rule15519policy2 = 
//{
//    "policy security-ips drop"
//};

static RuleMetaData rule15519policy3 = 
{
    "policy max-detect-ips drop"
};

static RuleMetaData *rule15519metadata[] =
{
    &rule15519service1,
//    &rule15519policy1,
//    &rule15519policy2,
    &rule15519policy3,
    NULL
};

RuleOption *rule15519options[] =
{
    &rule15519option0,
    &rule15519option1,
    &rule15519option2,
    &rule15519option3,
    NULL
};

Rule rule15519 = {
   
   /* rule header, akin to => tcp any any -> any any               */{
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "$HTTP_PORTS", /* SRCPORT   */
   
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
   
       "any", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid */
       15519, /* sigid */
       11, /* revision */
   
       "attempted-user", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "FILE-OFFICE Microsoft Office Excel BRAI record remote code execution attempt",     /* message */
       rule15519refs /* ptr to references */
       ,rule15519metadata
   },
   rule15519options, /* ptr to rule options */
   &rule15519eval, /* DO NOT use the built in detection function */
   0 /* am I initialized yet? */
};

// return 0 if next record type value is invalid. otherwise return 1
int rule15519eval_check_record_boundary(const uint8_t *cursor_temp, const uint8_t *end_of_payload)
{
    if (cursor_temp + 2 <= end_of_payload)
    {
        // 4200 (0x1068) is the biggest record type value, we are not looking at the proper record boundary
        if (read_little_16(cursor_temp) <= 0x1068)
            return 1;
    }
    
    return 0;
}

/* detection functions */
int rule15519eval(void *p) {
    const uint8_t *cursor_normal = 0, *end_of_payload = 0, *beg_of_payload = 0;
    SFSnortPacket *sp = (SFSnortPacket *) p;

    uint16_t max_format_ifmt = 0;
    uint16_t ifmt;        
    uint16_t record_size;
//    uint8_t  format_record_found = 0;

    DEBUG_WRAP(const char *name="rule15519eval";)
    DEBUG_WRAP(printf("%s: enter\n", name);)    

    if(sp == NULL)
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;
    
    // flowbits:isset "file.xls";
    if (processFlowbits(p, rule15519options[0]->option_u.flowBit) > 0) {
            // flow:established, to_client;
        if (checkFlow(p, rule15519options[1]->option_u.flowFlags) > 0 ) {

            if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &beg_of_payload, &end_of_payload) <= 0)
               return RULE_NOMATCH;

            cursor_normal = beg_of_payload;

            // content:"|1E 04|", depth 0;  // Format record
            // This content match is in the fast pattern matcher, guaranteeing we find
            // one and allowing the code to work as expected.
            while (contentMatch(p, rule15519options[2]->option_u.content, &cursor_normal) > 0) {

                if (cursor_normal + 4 > end_of_payload)
                    break;
                
                record_size = read_little_16(cursor_normal);                
                if (record_size > 4)  // must be bigger than 4 to be the size of Format record
                {
                    DEBUG_WRAP(printf("%s: Format (0x41e) record found. record size = 0x%04x\n", name, record_size);)
//                    format_record_found = 1;
                               
                    // check if we are looking at proper record boundary by testing next record type value
                    if (rule15519eval_check_record_boundary((cursor_normal + 2 + record_size), end_of_payload))
                    {
                        cursor_normal += 2;
                        ifmt = read_little_16(cursor_normal);
                        DEBUG_WRAP(printf("%s: ifmt = 0x%04x\n", name, ifmt);)
                            
                        if (ifmt > max_format_ifmt)
                            max_format_ifmt = ifmt;
                            
                        cursor_normal += record_size;           
                    }                    
                }
            }

            DEBUG_WRAP(printf("%s: max_format_ifmt = 0x%04x\n", name, max_format_ifmt);)

//            guaranteed to be here due to CONTENT_FAST_PATTERN
//            if (!format_record_found) // Format record was not found
//                return RULE_NOMATCH;
            
            cursor_normal = beg_of_payload; 
            
            // content:"Q|10|", depth 0;
            while (contentMatch(p, rule15519options[3]->option_u.content, &cursor_normal) > 0) {

                if (cursor_normal + 8 > end_of_payload)
                    break;
                
                record_size = read_little_16(cursor_normal);                
                if (record_size > 6)  // must be bigger than 6 to be the size of Format record
                {
                    DEBUG_WRAP(printf("%s: BRAI (0x1051) record found. record size = 0x%04x\n", name, record_size);)
                               
                    // check if we are looking at proper record boundary by testing next record type value
                    if (rule15519eval_check_record_boundary((cursor_normal + 2 + record_size), end_of_payload))
                    {
                        cursor_normal += 6;
                        ifmt = read_little_16(cursor_normal);
                        DEBUG_WRAP(printf("%s: ifmt = 0x%04x\n", name, ifmt);)
                            
                        if (ifmt > max_format_ifmt)
                            return RULE_MATCH;
                            
                        cursor_normal += record_size;
                    }
                }
            }
        }
    }
    return RULE_NOMATCH;
}

/*
Rule *rules[] = {
    &rule15519,
    NULL
};
*/
