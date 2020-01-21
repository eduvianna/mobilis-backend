import { Router } from 'express';

import MeasurementController from './app/controllers/MeasurementController';
import SensorController from './app/controllers/SensorController';
import WordController from './app/controllers/WordController';

const routes = new Router();

routes.post('/create-sensor', SensorController.store);
routes.put('/update-sensor', SensorController.update);
routes.get('/list-sensors', SensorController.index);

routes.post('/create-measurement', MeasurementController.store);
routes.get('/list-measurements', MeasurementController.index);

routes.post('/create-word', WordController.store);
routes.put('/update-word', WordController.update);
routes.get('/list-words', WordController.index);

export default routes;
