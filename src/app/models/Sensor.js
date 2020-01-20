import Sequelize, { Model } from 'sequelize';

class Sensor extends Model {
  static init(sequelize) {
    super.init(
      {
        sensor_id: Sequelize.STRING,
        name: Sequelize.STRING,
        description: Sequelize.STRING,
        type: Sequelize.STRING,
        word: Sequelize.INTEGER,
      },
      {
        sequelize,
        tableName: 'sensors',
      }
    );

    return this;
  }
}

export default Sensor;
