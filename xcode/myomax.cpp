#include "ext.h"
#include "ext_common.h"
#include "ext_obex.h"
#include "ext_time.h"
#include "ext_itm.h"
#include "myo.h"

typedef struct myomax
{
    t_object d_obj;
    
    TheMyo * mymyo;
    myo::Myo * thalmic;
    myo::Hub * hub;
    
    void *outlet;
} t_myomax;



void *myomax_new(t_symbol *s, long argc, t_atom *argv);
void myomax_free(t_myomax *x);

void myomax_bang(t_myomax *x);
void myomax_connect(t_myomax *x, t_symbol *s, long argc, t_atom *argv);
void myomax_process(t_myomax *x, t_symbol *s, long argc, t_atom *argv);

static t_class *s_myomax_class = NULL;





int C74_EXPORT main(void)
{
    t_class *c = class_new(	"myomax", (method)myomax_new, (method)myomax_free, sizeof(t_myomax), (method)0L, A_GIMME, 0);
    
    class_addmethod(c, (method)myomax_bang,			"bang",			0);
    class_addmethod(c, (method)myomax_connect,		"connect",		A_GIMME, 0);
    class_addmethod(c, (method)myomax_process,		"process",		A_GIMME, 0);
    
    class_register(CLASS_BOX, c);
    
    s_myomax_class = c;
    return 0;
}




// initial optional arg is delay time
void *myomax_new(t_symbol *s, long argc, t_atom *argv)
{
    t_myomax *x = (t_myomax *)object_alloc(s_myomax_class);
    
    x->mymyo    = new TheMyo();
    x->outlet   = outlet_new(x, NULL);
    
    return x;
}


void myomax_free(t_myomax *x)
{
    delete x->mymyo;
}



// "connect" message
void myomax_process(t_myomax *x, t_symbol *s, long argc, t_atom *argv)
{
    //ncueeiu
}


// "connect" message
void myomax_connect(t_myomax *x, t_symbol *s, long argc, t_atom *argv)
{
    
    // First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
    // publishing your application. The Hub provides access to one or more Myos.
    x->hub = new myo::Hub("com.example.emg-data-sample");
    
    post("Attempting to find a Myo...");
    
    // Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
    // immediately.
    // waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
    // if that fails, the function will return a null pointer.
    x->thalmic = x->hub->waitForMyo(1000);
    
    post("Connected to a Myo armband!");
    //
    // Next we enable EMG streaming on the found Myo.
    x->thalmic->setStreamEmg(myo::Myo::streamEmgEnabled);
    
    x->hub->addListener(x->mymyo);
    
    
}

// get EMG data
void myomax_bang(t_myomax *x)
{
    
    // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
    // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
    x->hub->run(1000/100);
    
    // After processing events, we get the EMG Data
    std::vector<float> emgData = x->mymyo->getEmgData();
    std::vector<float> accData = x->mymyo->getAccelerometerData();
    std::vector<float> gyroData = x->mymyo->getGyroscopeData();
    std::vector<float> eulerData = x->mymyo->getOrientationData();
    
    int numOfChannels = x->mymyo->getNumOfChannels();
    
    t_atom *outAtoms = new t_atom[numOfChannels];
    for (int k=0; k<numOfChannels; k++)
        atom_setfloat(&outAtoms[k], emgData[k]);
    outlet_anything(x->outlet, gensym("emg"), numOfChannels, outAtoms);
    delete[] outAtoms;
    
    int dim = 3;
    outAtoms = new t_atom[dim];
    for (int k=0; k<dim; k++)
        atom_setfloat(&outAtoms[k], accData[k]);
    outlet_anything(x->outlet, gensym("acc"), dim, outAtoms);
    delete[] outAtoms;
    
//    int dim = 3;
    outAtoms = new t_atom[dim];
    for (int k=0; k<dim; k++)
        atom_setfloat(&outAtoms[k], gyroData[k]);
    outlet_anything(x->outlet, gensym("gyro"), dim, outAtoms);
    delete[] outAtoms;
    
//    int dim = 3;
    outAtoms = new t_atom[dim];
    for (int k=0; k<dim; k++)
        atom_setfloat(&outAtoms[k], eulerData[k]);
    outlet_anything(x->outlet, gensym("euler"), dim, outAtoms);
    delete[] outAtoms;
    
    
    
}
