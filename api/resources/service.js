// show all data
// create data
/*
    FORMAT DATA
    collection
    name
    status
    value
*/

const fs= require('../sdk/fs');

module.exports = {
    create(req, res){
        const data = {
            'key'        : '',
            'collection' : req.params.collection,
            'name'       : req.params.name, 
            'status'     : req.params.status, 
            'value'      : req.params.value, 
            'created'    : new Date().getTime()
        }
        try{
            //insert data to fs
            fs.collection(
                req.params.collection.toString()
            ).add(
                data
            ).then((s) => {
                s.update({'key':s.id});
                res.json(data);
            })
        }catch(e){
            res.json(e);
        }
    },

    show(req, res){
        let data = [];
        fs.collection(
            req.params.collection.toString()
        ).orderBy('created', 'desc').get().then((s)=>{
            s.forEach((d) => {
                data.push(d.data())
            });
            res.json(data)
        })
    }
}